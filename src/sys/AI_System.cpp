#include <sys/AI_System.hpp>
#include <man/Manager_t.hpp>

#include <ent/Entity_t.hpp>

#include <cmp/AI_Component.hpp>
#include <cmp/MovementComponent.hpp>

#include <utils/AI_Constants.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

void
AI_System::init() noexcept { }

bool
AI_System::update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept {
    auto& ai_cmp_vec = context->getAI_Cmps();
    
    std::for_each(begin(ai_cmp_vec), end(ai_cmp_vec), [&](std::unique_ptr<AI_Component>& ai_cmp) {
        auto& ent     = context->getEntityByID( ai_cmp->getEntityID() );
        auto* mov_cmp = ent->getComponent<MovementComponent>();

        switch (ai_cmp->current_behavior) {
        case AI_behaviour::patrol_b : patrol(ai_cmp, mov_cmp);
            break;
        
        case AI_behaviour::chase_b : {
                auto& pj = context->getEntityByID( context->getPlayerID() );
                auto& pj_pos = pj->getComponent<MovementComponent>()->coords;   
                chase(ai_cmp, mov_cmp, pj_pos);
            }
            break;

        case AI_behaviour::runaway_b : {
                auto& pj = context->getEntityByID( context->getPlayerID() );
                auto& pj_pos = pj->getComponent<MovementComponent>()->coords;   
                run_away(ai_cmp, mov_cmp, pj_pos);
            }
            break;

        case AI_behaviour::pursue_b : {
                auto& pj = context->getEntityByID( context->getPlayerID() );
                auto* pj_mov = pj->getComponent<MovementComponent>();   
                pursue(ai_cmp, mov_cmp, pj_mov);
            }
            break;

        case AI_behaviour::evade_b : {
                auto& pj = context->getEntityByID( context->getPlayerID() );
                auto* pj_mov = pj->getComponent<MovementComponent>();   
                evade(ai_cmp, mov_cmp, pj_mov);
            }
            break;

        default: 
                mov_cmp->dir.x.number = mov_cmp->dir.y.number = 0;
                mov_cmp->accel_to_target.x.number = mov_cmp->accel_to_target.y.number = 0;
            break;
        }
    });

    separation(context, ai_cmp_vec);

    return true;
}


/* CONPLEX B. */
void 
AI_System::patrol(std::unique_ptr<AI_Component>& ai_cmp, MovementComponent* mov_cmp) noexcept {
    auto& target = ai_cmp->target_vec.at(ai_cmp->target_index);
    
    if( !arrive(mov_cmp, target) ) {
        if(auto new_target = updatePatrol(ai_cmp))
            arrive(mov_cmp, (*new_target).get());
    }
}

void 
AI_System::chase(std::unique_ptr<AI_Component>& ai_cmp, MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept {
    arrive(mov_cmp, target_pos);
}

void 
AI_System::run_away(std::unique_ptr<AI_Component>& ai_cmp, MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept {
    if( !leave(mov_cmp, target_pos) ) {
        mov_cmp->dir.x.number = mov_cmp->dir.y.number = 0;
        mov_cmp->accel_to_target.x.number = mov_cmp->accel_to_target.y.number = 0;
    }
}

void
AI_System::pursue(std::unique_ptr<AI_Component>& ai_cmp, MovementComponent* mov_cmp, MovementComponent* target_mov_cmp) noexcept {
    auto& target_pos    = target_mov_cmp->coords;
    auto  predicted_pos = target_pos + target_mov_cmp->dir;

    arrive(mov_cmp, predicted_pos);
}

void
AI_System::evade(std::unique_ptr<AI_Component>& ai_cmp, MovementComponent* mov_cmp, MovementComponent* target_mov_cmp) noexcept {
    auto& target_pos    = target_mov_cmp->coords;
    auto  predicted_pos = target_pos + target_mov_cmp->dir;

    if( !leave(mov_cmp, predicted_pos) ) {
        mov_cmp->dir.x.number = mov_cmp->dir.y.number = 0;
        mov_cmp->accel_to_target.x.number = mov_cmp->accel_to_target.y.number = 0;
    }
}  


/* BASIC BEHAVIOURS FUNCTIONS */
bool
AI_System::arrive(MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept {
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

bool
AI_System::leave(MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept {
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
void 
AI_System::separation(const std::unique_ptr<Manager_t>& context, std::vector<std::unique_ptr<AI_Component>>& AI_cmps) noexcept {
    auto end_it = end(AI_cmps);
    
    for(auto ai_it = begin(AI_cmps) ; ai_it < end_it ; ++ai_it) {
        auto& ai_ent     = context->getEntityByID( (*ai_it)->getEntityID() );
        auto* ai_mov_cmp = ai_ent->getComponent<MovementComponent>();

        for(auto comparision_it = ai_it+1 ; comparision_it < end_it ; ++comparision_it) {
            auto& comparision_ent     = context->getEntityByID( (*comparision_it)->getEntityID() );
            auto* comparision_mov_cmp = comparision_ent->getComponent<MovementComponent>();

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


/* AUX FUNCTIONS */
AI_System::optVec2_refw 
AI_System::updatePatrol(std::unique_ptr<AI_Component>& ai_cmp) noexcept {
    auto& route  = ai_cmp->target_vec;
    auto& index  = ai_cmp->target_index;

    auto index_fwd = (index+1) % route.size();

    if(index_fwd != index) {
        index = index_fwd;
        return std::ref(route.at(index));
    }
    
    return { };
}

AI_System::optVec2_refw 
AI_System::updateRoute(std::unique_ptr<AI_Component>& ai_cmp) noexcept {
    auto& route  = ai_cmp->target_vec;
    auto& index  = ai_cmp->target_index;

    auto index_fwd = index + 1;

    if(index_fwd < route.size()) {
        index = index_fwd;
        return std::ref(route.at(index));
    }

    return { };
}


} //NS