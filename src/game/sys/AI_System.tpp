#include <game/sys/AI_System.hpp>
#include <game/cmp/AI_Component.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/CombatComponent.hpp>
#include <game/utils/AI_Constants.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <algorithm>

namespace AIP {

template <typename Context_t>
bool
AI_System<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& enemies_ids = context.template getEnemyIDs();
    
    std::for_each(begin(enemies_ids), end(enemies_ids), [&](BECS::entID eid) {
        auto& ai_cmp  = context.template getCmpByEntityID<AI_Component>( eid );
        auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>( eid );
        auto& pj_mov  = context.template getCmpByEntityID<MovementComponent>( context.getPlayerID() );
        auto& pj_pos  = pj_mov.coords;

        auto  target_dir = pj_pos - mov_cmp.coords;
        auto  distance2  = target_dir.length2();

        if( distance2.getNoScaled() > (200l * 200l) ) {         //Terrorismo en estad0 pur0
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
        
            case AI_behaviour::chase_b : chase(mov_cmp, pj_pos);
            break;

            case AI_behaviour::runaway_b : run_away(mov_cmp, pj_pos);
            break;

            case AI_behaviour::pursue_b : pursue(mov_cmp, pj_mov);
            break;

            case AI_behaviour::evade_b : evade(mov_cmp, pj_mov);
            break;

            case AI_behaviour::attack_b : attack(mov_cmp, pj_pos, context);
            break;

        default: 
                mov_cmp.dir.x.number             = mov_cmp.dir.y.number             = 0;
                mov_cmp.accel_to_target.x.number = mov_cmp.accel_to_target.y.number = 0;
            break;
        }

    });

    //cuando haya mas de un bando habra que cambiarlo
    separation(context);
    cohesion(context, enemies_ids);

    return true;
}


/* CONPLEX B. */
template <typename Context_t>
void 
AI_System<Context_t>::patrol(AI_Component& ai_cmp, MovementComponent& mov_cmp) noexcept {
    auto& target = ai_cmp.target_vec.at(ai_cmp.target_index);
    
    if( !arrive(mov_cmp, target) ) {
        if( auto new_target = updatePatrol(ai_cmp) )
            arrive(mov_cmp, (*new_target).get());
    }

}

template <typename Context_t>
void 
AI_System<Context_t>::chase(MovementComponent& mov_cmp, fvec2<fint_t<int64_t>>& target_pos) noexcept {
    arrive(mov_cmp, target_pos);
}

template <typename Context_t>
void 
AI_System<Context_t>::run_away(MovementComponent& mov_cmp, fvec2<fint_t<int64_t>>& target_pos) noexcept {
    if( !leave(mov_cmp, target_pos) ) {
        mov_cmp.dir.x.number = mov_cmp.dir.y.number = 0;
        mov_cmp.accel_to_target.x.number = mov_cmp.accel_to_target.y.number = 0;
    }
}

template <typename Context_t>
void
AI_System<Context_t>::pursue(MovementComponent& mov_cmp, MovementComponent& target_mov_cmp) noexcept {
    auto  predicted_pos { target_mov_cmp.coords + target_mov_cmp.dir };

    arrive(mov_cmp, predicted_pos);
}

template <typename Context_t>
void
AI_System<Context_t>::evade(MovementComponent& mov_cmp, MovementComponent& target_mov_cmp) noexcept {
    auto  predicted_pos { target_mov_cmp.coords + target_mov_cmp.dir };

    if( !leave(mov_cmp, predicted_pos) ) {
        mov_cmp.dir.x.number = mov_cmp.dir.y.number = 0;
        mov_cmp.accel_to_target.x.number = mov_cmp.accel_to_target.y.number = 0;
    }
}  

template <typename Context_t>
void
AI_System<Context_t>::attack(MovementComponent& mov_cmp, fvec2<fint_t<int64_t>>& target_pos, Context_t& context) noexcept {
    auto& combat_cmp = context.template getCmpByEntityID<CombatComponent>( mov_cmp.getEntityID() );
    
    if(combat_cmp.current_attack_cd.number <= 0l) {
        combat_cmp.current_attack_cd = combat_cmp.attack_cd;
        //attack_msg.emplace_back(mov_cmp.getEntityID(), context.getPlayerID(), combat_cmp.damage); //rediseño para X enemigo
    }
    
    arrive(mov_cmp, target_pos);
}


/* BASIC BEHAVIOURS FUNCTIONS */
template <typename Context_t>
bool
AI_System<Context_t>::arrive(MovementComponent& mov_cmp, fvec2<fint_t<int64_t>>& target_pos) noexcept {
    auto& my_coords = mov_cmp.coords;
    auto& my_accel  = mov_cmp.accel_to_target;
    auto& my_direct = mov_cmp.dir;

    auto            target_dir   { target_pos - my_coords };
    auto            distance2    { target_dir.length2()   };
    fint_t<int64_t> target_speed { };

    if(distance2 < ENT_ARRIVE_DIST2)
        return false;

    if(distance2 > ENT_SLOW_DIST2)
        target_speed = ENT_MAX_SPEED;
    else
        target_speed = ENT_MAX_SPEED * ( target_dir.length_fix() / ENT_SLOW_DIST );
    
    target_dir.normalize();
    target_dir *= target_speed;

    my_accel  = (target_dir - my_direct);
    my_accel /= ENT_TIME_TO_TARGET;

    if(my_accel.length2() > ENT_MAX_ACCEL2) {
        my_accel.normalize();
        my_accel *= ENT_MAX_ACCEL;
    }

    return true;
}

template <typename Context_t>
bool
AI_System<Context_t>::leave(MovementComponent& mov_cmp, fvec2<fint_t<int64_t>>& target_pos) noexcept {
    auto& my_coords = mov_cmp.coords;
    auto& my_accel  = mov_cmp.accel_to_target;
    auto& my_direct = mov_cmp.dir;

    auto            target_dir   { my_coords - target_pos };
    auto            distance2    { target_dir.length2()   };
    fint_t<int64_t> target_speed { };

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
AI_System<Context_t>::separation(Context_t& context) noexcept {
    auto& mov_vec = context.template getComponentVector<MovementComponent>();
    auto  end_it  = end(mov_vec);
    
    for(auto mov_it = begin(mov_vec); mov_it < end_it; ++mov_it) {
        auto& mov_cmp   = *mov_it;
        auto& sep_force = mov_cmp.separation_force;

        std::for_each(mov_it+1, end_it, [&](MovementComponent& ally_mov_cmp) {
            auto diff_vec  { mov_cmp.coords - ally_mov_cmp.coords };
            auto distance2 { diff_vec.length2() };

            if(distance2 < ENT_SEPARATION_DIST2) {
                auto strength { std::min(DECAY_COEFICIENT / distance2, ENT_MAX_ACCEL) };
                diff_vec.normalize();
                auto result   { diff_vec * strength };

                sep_force                     += result;
                ally_mov_cmp.separation_force += result * -1;
            }
        });

        if(sep_force.length2() > ENT_MAX_ACCEL2) {
            sep_force.normalize();
            sep_force *= ENT_MAX_ACCEL;
        }

    }// END FOR AI
}

template <typename Context_t>
void
AI_System<Context_t>::cohesion(Context_t& context, std::vector<BECS::entID>& eids) noexcept {
    auto end_it = end(eids);
    
    for(auto eid_it = begin(eids); eid_it < end_it; ++eid_it) {
        auto& mov_cmp  = context.template getCmpByEntityID<MovementComponent>( (*eid_it) );
        auto& cohesion = mov_cmp.cohesion_force;

        std::for_each(eid_it+1, end_it, [&](BECS::entID ally_eid){
            auto& ally_mov_cmp = context.template getCmpByEntityID<MovementComponent>( ally_eid );
        
            auto diff_vec  { ally_mov_cmp.coords - mov_cmp.coords };
            auto distance2 { diff_vec.length2() };

            if(distance2 < ENT_COHESION_DIST2) {
                auto strength { std::min(distance2 / (DECAY_COEFICIENT/2), ENT_MAX_ACCEL) };
                diff_vec.normalize();
                auto result   { diff_vec * strength };

                cohesion                    += result;
                ally_mov_cmp.cohesion_force += result * -1;
            }
        });

        if(cohesion.length2() > ENT_MAX_ACCEL2) {
            cohesion.normalize();
            cohesion *= ENT_MAX_ACCEL;
        }
        
    }// END FOR AI
}


/* AUX FUNCTIONS */
template <typename Context_t>
typename AI_System<Context_t>::optVec2_refw 
AI_System<Context_t>::updatePatrol(AI_Component& ai_cmp) noexcept {
    optVec2_refw next_pos  { };
    auto&        route     = ai_cmp.target_vec;
    auto&        index     = ai_cmp.target_index;
    auto         index_fwd { (index+1) % route.size() };

    if(index_fwd != index) {
        index = index_fwd;
        next_pos = std::ref(route.at(index));
    }
    
    return next_pos;
}

template <typename Context_t>
typename AI_System<Context_t>::optVec2_refw 
AI_System<Context_t>::updateRoute(AI_Component& ai_cmp) noexcept {
    optVec2_refw next_pos  { };
    auto&        route     = ai_cmp.target_vec;
    auto&        index     = ai_cmp.target_index;
    auto         index_fwd { index + 1 };

    if(index_fwd < route.size()) {
        index = index_fwd;
        next_pos = std::ref(route.at(index));
    }

    return next_pos;
}

} //NS