#include <sys/AI_System.hpp>

#include <ent/Entity_t.hpp>

#include <cmp/AI_Component.hpp>
#include <cmp/MovementComponent.hpp>
#include <cmp/CombatComponent.hpp>

#include <utils/AI_Constants.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

template <typename Context_t>
bool
AI_System<Context_t>::update(Context_t& context, const fixed64_t DeltaTime) noexcept {
    auto& ai_cmp_vec = context.template getComponentVector<AI_Component>();
    
    std::for_each(begin(ai_cmp_vec), end(ai_cmp_vec), [&](AI_Component& ai_cmp) {
        auto& ent     = context.getEntityByID( ai_cmp.getEntityID() );
        auto* mov_cmp = ent.template getComponent<MovementComponent>();

        auto& pj     = context.getEntityByID( context.getPlayerID() );
        auto* pj_mov = pj.template getComponent<MovementComponent>();
        auto& pj_pos = pj_mov->coords;

        auto  target_dir = pj_pos - mov_cmp->coords;
        auto  distance2  = target_dir.length2();

        if( distance2.getNoScaled() > (200l * 200l) ) {
            ai_cmp.current_behavior = AI_behaviour::patrol_b;
        }
        if( distance2.getNoScaled() > (130l * 130l) && distance2.getNoScaled() < (200l * 200l) ) {
            ai_cmp.current_behavior = AI_behaviour::chase_b;
        } 
        if( distance2.getNoScaled() < (130l * 130l) ) {
            ai_cmp.current_behavior = AI_behaviour::attack_b;
        }

        switch (ai_cmp.current_behavior) {
            case AI_behaviour::patrol_b : patrol(ai_cmp, mov_cmp);
            break;
        
            case AI_behaviour::chase_b : chase(ai_cmp, mov_cmp, pj_pos);
            break;

            case AI_behaviour::runaway_b : run_away(ai_cmp, mov_cmp, pj_pos);
            break;

            case AI_behaviour::pursue_b : pursue(ai_cmp, mov_cmp, pj_mov);
            break;

            case AI_behaviour::evade_b : evade(ai_cmp, mov_cmp, pj_mov);
            break;

            case AI_behaviour::attack_b : attack(ai_cmp, mov_cmp, pj_pos, context);
            break;

        default: 
                mov_cmp->dir.x.number = mov_cmp->dir.y.number = 0;
                mov_cmp->accel_to_target.x.number = mov_cmp->accel_to_target.y.number = 0;
            break;
        }
    });

    //cuando haya mas de un bando habra que cambiarlo
    separation(context, ai_cmp_vec);
    cohesion(context, ai_cmp_vec);

    return true;
}


/* CONPLEX B. */
template <typename Context_t>
void 
AI_System<Context_t>::patrol(AI_Component& ai_cmp, MovementComponent* mov_cmp) noexcept {
    auto& target = ai_cmp.target_vec.at(ai_cmp.target_index);
    
    if( !arrive(mov_cmp, target) ) {
        if(auto new_target = updatePatrol(ai_cmp))
            arrive(mov_cmp, (*new_target).get());
    }

}

template <typename Context_t>
void 
AI_System<Context_t>::chase(AI_Component& ai_cmp, MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept {
    arrive(mov_cmp, target_pos);
}

template <typename Context_t>
void 
AI_System<Context_t>::run_away(AI_Component& ai_cmp, MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept {
    if( !leave(mov_cmp, target_pos) ) {
        mov_cmp->dir.x.number = mov_cmp->dir.y.number = 0;
        mov_cmp->accel_to_target.x.number = mov_cmp->accel_to_target.y.number = 0;
    }
}

template <typename Context_t>
void
AI_System<Context_t>::pursue(AI_Component& ai_cmp, MovementComponent* mov_cmp, MovementComponent* target_mov_cmp) noexcept {
    auto& target_pos    = target_mov_cmp->coords;
    auto  predicted_pos = target_pos + target_mov_cmp->dir;

    arrive(mov_cmp, predicted_pos);
}

template <typename Context_t>
void
AI_System<Context_t>::evade(AI_Component& ai_cmp, MovementComponent* mov_cmp, MovementComponent* target_mov_cmp) noexcept {
    auto& target_pos    = target_mov_cmp->coords;
    auto  predicted_pos = target_pos + target_mov_cmp->dir;

    if( !leave(mov_cmp, predicted_pos) ) {
        mov_cmp->dir.x.number = mov_cmp->dir.y.number = 0;
        mov_cmp->accel_to_target.x.number = mov_cmp->accel_to_target.y.number = 0;
    }
}  

template <typename Context_t>
void
AI_System<Context_t>::attack(AI_Component& ai_cmp  , MovementComponent* mov_cmp, fixed_vec2& target_pos, Context_t& context) noexcept {
    auto& ent = context.getEntityByID(ai_cmp.getEntityID());
    auto* combat_cmp = ent.template getComponent<CombatComponent>();
    
    if(combat_cmp->current_attack_cd.number <= 0l) {
        combat_cmp->current_attack_cd = combat_cmp->attack_cd;
        attack_msg.emplace_back(ai_cmp.getEntityID(), context.getPlayerID(), combat_cmp->damage);
        std::cout << "MUEREEEE\n\n";
    }
    
    arrive(mov_cmp, target_pos);
}


/* BASIC BEHAVIOURS FUNCTIONS */
template <typename Context_t>
bool
AI_System<Context_t>::arrive(MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept {
    auto& my_coords = mov_cmp->coords;
    auto& my_accel  = mov_cmp->accel_to_target;
    auto& my_direct = mov_cmp->dir;

    auto  target_dir = target_pos - my_coords;
    auto  distance2  = target_dir.length2();
    fixed64_t target_speed { };

    if(distance2 < ENT_ARRIVE_DIST2)
        return false;

    //si esta lejos intenta alcanzar max speed, sino interpola [max_speed, 0]
    if(distance2 > ENT_SLOW_DIST2)
        target_speed = ENT_MAX_SPEED;
    else
        target_speed = ENT_MAX_SPEED * ( target_dir.length_fix() / ENT_SLOW_DIST );
    
    //calculamos la aceleracion objetivo como la diferencia de  (deseada - actual) 
    target_dir.normalize();
    target_dir *= target_speed;

    my_accel  = (target_dir - my_direct);
    my_accel /= ENT_TIME_TO_TARGET;

    //ajustamos la aceleracion para que no sea muy alta.
    if(my_accel.length2() > ENT_MAX_ACCEL2) {
        my_accel.normalize();
        my_accel *= ENT_MAX_ACCEL;
    }

    return true;
}

template <typename Context_t>
bool
AI_System<Context_t>::leave(MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept {
    auto& my_coords = mov_cmp->coords;
    auto& my_accel  = mov_cmp->accel_to_target;
    auto& my_direct = mov_cmp->dir;

    auto  target_dir = my_coords - target_pos;
    auto  distance2  = target_dir.length2();
    fixed64_t target_speed { };

    if(distance2 > ENT_FLEE_DIST2)
        return false;

    //si esta lejos intenta alcanzar max speed, sino interpola [max_speed, 0]
    if(distance2 < ENT_FAR_SLOW_DIST2)
        target_speed = ENT_MAX_SPEED;
    else
        target_speed = ENT_MAX_SPEED * ( (ENT_FAR_SLOW_DIST - target_dir.length_fix()) / ENT_FAR_SLOW_DIST );

    //calculamos la aceleracion objetivo como la diferencia de  (deseada - actual) 
    target_dir.normalize();
    target_dir *= target_speed;

    my_accel  = (target_dir - my_direct);
    my_accel /= ENT_TIME_TO_TARGET;

    //ajustamos la aceleracion para que no sea muy alta.
    if(my_accel.length2() > ENT_MAX_ACCEL2) {
        my_accel.normalize();
        my_accel *= ENT_MAX_ACCEL;
    }

    return true;
}


/* FLOCKING B. FUNCTIONS */
template <typename Context_t>
void 
AI_System<Context_t>::separation(Context_t& context, std::vector<AI_Component>& AI_cmps) noexcept {
    auto end_it = end(AI_cmps);
    
    for(auto ai_it = begin(AI_cmps) ; ai_it < end_it ; ++ai_it) {
        auto& ai_ent     = context.getEntityByID( (*ai_it).getEntityID() );
        auto* ai_mov_cmp = ai_ent.template getComponent<MovementComponent>();

        for(auto comparision_it = ai_it+1 ; comparision_it < end_it ; ++comparision_it) {
            auto& comparision_ent     = context.getEntityByID( (*comparision_it).getEntityID() );
            auto* comparision_mov_cmp = comparision_ent.template getComponent<MovementComponent>();

            auto diff_vec  = ai_mov_cmp->coords - comparision_mov_cmp->coords;
            auto distance2 = diff_vec.length2();

            if(distance2 < ENT_SEPARATION_DIST2) {
                auto strength = std::min(DECAY_COEFICIENT / distance2, ENT_MAX_ACCEL);
                diff_vec.normalize();
                auto result   = diff_vec * strength;

                ai_mov_cmp->separation_force          += result;
                comparision_mov_cmp->separation_force += result * -1;
            }
        }// END FOR COMPARISION

        if(ai_mov_cmp->separation_force.length2() > ENT_MAX_ACCEL2) {
            ai_mov_cmp->separation_force.normalize();
            ai_mov_cmp->separation_force *= ENT_MAX_ACCEL;
        }

    }// END FOR AI
}

template <typename Context_t>
void
AI_System<Context_t>::cohesion(Context_t& context, std::vector<AI_Component>& AI_cmps) noexcept {
    auto end_it = end(AI_cmps);
    
    for(auto ai_it = begin(AI_cmps) ; ai_it < end_it ; ++ai_it) {
        auto& ai_ent     = context.getEntityByID( (*ai_it).getEntityID() );
        auto* ai_mov_cmp = ai_ent.template getComponent<MovementComponent>();
        auto& ai_centre  = ai_mov_cmp->cohesion_force;
        auto& ai_count   = ai_mov_cmp->cohesion_count;

        for(auto comparision_it = ai_it+1 ; comparision_it < end_it ; ++comparision_it) {
            auto& comparision_ent     = context.getEntityByID( (*comparision_it).getEntityID() );
            auto* comparision_mov_cmp = comparision_ent.template getComponent<MovementComponent>();
            auto& comparision_centre  = comparision_mov_cmp->cohesion_force;
            auto& comparision_count   = comparision_mov_cmp->cohesion_count;

            auto diff_vec = ai_mov_cmp->coords - comparision_mov_cmp->coords;

            if(diff_vec.length2() < ENT_COHESION_DIST2) {
                ai_centre += comparision_mov_cmp->coords;
                ai_count  += 1;
                comparision_centre += ai_mov_cmp->coords;
                comparision_count  += 1;
            }
        }// END FOR COMPARISION

        if(ai_count.number > 0) {
            ai_centre        /= ai_count;
            auto target_dir   = ai_centre - ai_mov_cmp->coords;
            auto target_speed = ENT_MAX_SPEED * ( target_dir.length_fix() / (ENT_SEPARATION_DIST/2) );
        
            target_dir.normalize();
            target_dir *= target_speed;
            target_dir /= ENT_TIME_TO_TARGET;

            //ajustamos la aceleracion para que no sea muy alta.
            if(target_dir.length2() > ENT_MAX_ACCEL2) {
                target_dir.normalize();
                target_dir *= ENT_MAX_ACCEL;
            }
            
            ai_centre = target_dir;
        }
    }// END FOR AI
}

/* AUX FUNCTIONS */
template <typename Context_t>
typename AI_System<Context_t>::optVec2_refw 
AI_System<Context_t>::updatePatrol(AI_Component& ai_cmp) noexcept {
    auto& route  = ai_cmp.target_vec;
    auto& index  = ai_cmp.target_index;

    auto index_fwd = (index+1) % route.size();

    if(index_fwd != index) {
        index = index_fwd;
        return std::ref(route.at(index));
    }
    
    return { };
}

template <typename Context_t>
typename AI_System<Context_t>::optVec2_refw 
AI_System<Context_t>::updateRoute(AI_Component& ai_cmp) noexcept {
    auto& route  = ai_cmp.target_vec;
    auto& index  = ai_cmp.target_index;

    auto index_fwd = index + 1;

    if(index_fwd < route.size()) {
        index = index_fwd;
        return std::ref(route.at(index));
    }

    return { };
}

} //NS