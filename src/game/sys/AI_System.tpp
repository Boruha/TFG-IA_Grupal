#include <game/sys/AI_System.hpp>

#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/CombatComponent.hpp>
#include <game/utils/AI_Constants.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

template <typename Context_t>
void
AI_System<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& enemies_ids = context.template getEnemyIDs();
    auto& allies_ids  = context.template getAllyIDs();
    
    //update IA units
    std::for_each(begin(enemies_ids), end(enemies_ids), [&](BECS::entID eid) {     
        auto& ai_cmp  = context.template getCmpByEntityID<AI_Component>( eid );
        auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>( eid );
        
        decisionMakingIA(context, eid, allies_ids);

        switch (ai_cmp.current_behavior) {
            case AI_behaviour::patrol_b : patrol(context, eid);
            break;
        
            case AI_behaviour::chase_b : chase(context, eid);
            break;

            case AI_behaviour::attack_b : attack(context, eid);
            break;

            default: 
                mov_cmp.dir.x.number             = mov_cmp.dir.y.number             = 0;
                mov_cmp.accel_to_target.x.number = mov_cmp.accel_to_target.y.number = 0;
            break;
        }
    });

    auto comand = AI_behaviour::no_b;
    
    if( !comand_msg.empty() ) {
        comand = comand_msg.front().action;
        comand_msg.pop();
    }
    
    //update PJ units
    std::for_each(begin(allies_ids), end(allies_ids), [&](BECS::entID eid) {     
        auto& ai_cmp  = context.template getCmpByEntityID<AI_Component>( eid );
        auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>( eid );

        decisionMakingPJ(context, eid, enemies_ids, comand);

        switch (ai_cmp.current_behavior) {
            case AI_behaviour::follow_b : chase(context, eid);
            break;
        
            case AI_behaviour::chase_b : chase(context, eid);
            break;

            case AI_behaviour::attack_b : attack(context, eid);
            break;

            default: 
                mov_cmp.dir.x.number             = mov_cmp.dir.y.number             = 0;
                mov_cmp.accel_to_target.x.number = mov_cmp.accel_to_target.y.number = 0;
            break;
        }
    });

    separation(context);
    cohesion(context, enemies_ids);
    cohesion(context, allies_ids);

}


/* COMPLEX B. */
template <typename Context_t>
constexpr void
AI_System<Context_t>::patrol(Context_t& context, BECS::entID eid) noexcept {
    if( !arrive(context, eid) ) {
        if( updatePatrol(context, eid) )
            arrive(context, eid);
    }
}

template <typename Context_t>
constexpr void 
AI_System<Context_t>::chase(Context_t& context, BECS::entID eid) noexcept {
    auto& ai_cmp      = context.template getCmpByEntityID<AI_Component>( eid );
    auto& mov_cmp     = context.template getCmpByEntityID<MovementComponent>( ai_cmp.target_ent );
    ai_cmp.target_pos = mov_cmp.coords;
    
    arrive(context, eid);
}

template <typename Context_t>
constexpr void
AI_System<Context_t>::attack(Context_t& context, BECS::entID eid) noexcept {
    auto& combat_cmp = context.template getCmpByEntityID<CombatComponent>( eid );
    auto& ai_cmp     = context.template getCmpByEntityID<AI_Component>( eid );
    
    if(combat_cmp.current_attack_cd.number <= 0l) {
        combat_cmp.current_attack_cd = combat_cmp.attack_cd;
        attack_msg.emplace(eid, ai_cmp.target_ent, combat_cmp.damage); //rediseño para X enemigo
    }    
}

template <typename Context_t>
constexpr void 
AI_System<Context_t>::run_away(Context_t& context, BECS::entID eid) noexcept {
    auto& ai_cmp = context.template getCmpByEntityID<AI_Component>(eid);
    
    if( !leave(context, eid) ) 
        ai_cmp.current_behavior = AI_behaviour::no_b;
    
}

template <typename Context_t>
constexpr void
AI_System<Context_t>::pursue(Context_t& context, BECS::entID eid) noexcept {
    auto& ai_cmp        = context.template getCmpByEntityID<AI_Component>(eid);
    auto& enemy_mov_cmp = context.template getCmpByEntityID<MovementComponent>(ai_cmp.target_ent);

    ai_cmp.target_pos = enemy_mov_cmp.coords + enemy_mov_cmp.dir;

    arrive(context, eid);
}

template <typename Context_t>
constexpr void
AI_System<Context_t>::evade(Context_t& context, BECS::entID eid) noexcept {
    auto& ai_cmp  = context.template getCmpByEntityID<AI_Component>(eid);
    auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>(ai_cmp.target_ent);
    
    ai_cmp.target_pos = mov_cmp.coords + mov_cmp.dir;

    if( !leave(context, eid) )
        ai_cmp.current_behavior = AI_behaviour::no_b;

}  


/* BASIC BEHAVIOURS FUNCTIONS */

template <typename Context_t>
constexpr bool
AI_System<Context_t>::arrive(Context_t& context, BECS::entID eid) noexcept {
    auto& ai_cmp  = context.template getCmpByEntityID<AI_Component>(eid);
    auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>(eid);
    
    auto& my_coords = mov_cmp.coords;
    auto& my_accel  = mov_cmp.accel_to_target;
    auto& my_direct = mov_cmp.dir;

    auto            target_dir   { ai_cmp.target_pos - my_coords };
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
constexpr bool
AI_System<Context_t>::leave(Context_t& context, BECS::entID eid) noexcept {
    auto& ai_cmp  = context.template getCmpByEntityID<AI_Component>(eid);
    auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>(eid);
    
    auto& my_coords = mov_cmp.coords;
    auto& my_accel  = mov_cmp.accel_to_target;
    auto& my_direct = mov_cmp.dir;

    auto            target_dir   { my_coords - ai_cmp.target_pos };
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
constexpr void 
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
                auto strength { std::min(DECAY_COEFICIENT_SEP / distance2, ENT_MAX_ACCEL) };
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
constexpr void
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
                auto strength { std::min(distance2 / DECAY_COEFICIENT_COH, ENT_MAX_ACCEL) };
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


/* DECISION FUNCTIONS */
template <typename Context_t>
constexpr void
AI_System<Context_t>::decisionMakingIA(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids) noexcept {
        auto& ai_cmp  = context.template getCmpByEntityID<AI_Component>( eid );
        auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>( eid );

        auto& curr_behavior = ai_cmp.current_behavior;

        if( curr_behavior == AI_behaviour::patrol_b || curr_behavior == AI_behaviour::no_b ) {
            if( findNearEnemy(context, eid, enemy_eids) ) {
                curr_behavior = AI_behaviour::chase_b;
                return;
            }
        }

        if( curr_behavior == AI_behaviour::chase_b || curr_behavior == AI_behaviour::attack_b ) {
            auto& combat_cmp  = context.template getCmpByEntityID<CombatComponent>( ai_cmp.target_ent );

            auto  target_dir = ai_cmp.target_pos - mov_cmp.coords;
            auto  distance2  = target_dir.length2();
            
            if( distance2 > VISION_DIST2 || combat_cmp.health <= 0 ) {
                curr_behavior     = AI_behaviour::patrol_b;
                ai_cmp.target_ent = 0u;
                ai_cmp.target_pos = ai_cmp.target_vec.at(ai_cmp.target_index);
                return;
            }

            if(distance2 < ATTACK_DIST2)
                curr_behavior = AI_behaviour::attack_b;
            else
                curr_behavior = AI_behaviour::chase_b;
        }

        if( curr_behavior == AI_behaviour::no_b )
            curr_behavior = AI_behaviour::patrol_b;
}

template <typename Context_t>
constexpr void
AI_System<Context_t>::decisionMakingPJ(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids, AI_behaviour comand) noexcept {
        auto& ai_cmp  = context.template getCmpByEntityID<AI_Component>( eid );

        auto& curr_behavior = ai_cmp.current_behavior;

        if( curr_behavior == AI_behaviour::chase_b || curr_behavior == AI_behaviour::attack_b ) {
            auto& mov_cmp    = context.template getCmpByEntityID<MovementComponent>( eid );
            auto& combat_cmp = context.template getCmpByEntityID<CombatComponent>( ai_cmp.target_ent );

            auto  target_dir = ai_cmp.target_pos - mov_cmp.coords;
            auto  distance2  = target_dir.length2();
            
            if(distance2 < ATTACK_DIST2)
                comand = AI_behaviour::attack_b;
            else
                comand = AI_behaviour::chase_b;
        
            if( distance2 > VISION_DIST2 || combat_cmp.health <= 0 )
                comand = AI_behaviour::follow_b;
        }

        if(comand != AI_behaviour::no_b) {
            
            switch (comand) {
                case AI_behaviour::follow_b : {
                        auto  pj_eid  = context.template getPlayerID();
                        auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>( pj_eid );

                        curr_behavior     = AI_behaviour::follow_b;
                        ai_cmp.target_ent = pj_eid;
                        ai_cmp.target_pos = mov_cmp.coords;
                } break;
            
                case AI_behaviour::chase_b : {
                        if( findNearEnemy(context, eid, enemy_eids) )
                            curr_behavior = AI_behaviour::chase_b;
                } break;

                case AI_behaviour::attack_b : {
                        curr_behavior = AI_behaviour::attack_b;
                } break;

                default: 
                break;
            }
        }

}


/* AUX FUNCTIONS */
template <typename Context_t> constexpr 
bool 
AI_System<Context_t>::findNearEnemy(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids) noexcept {
    auto  result    { false };
    auto& ai_cmp    = context.template getCmpByEntityID<AI_Component>( eid );
    auto& mov_cmp   = context.template getCmpByEntityID<MovementComponent>( eid );
    auto& my_coords = mov_cmp.coords;
    
    auto dist { VISION_DIST2 };

    std::for_each(begin(enemy_eids), end(enemy_eids), [&](BECS::entID enemy_eid) {
        auto& enemy_mov_cmp = context.template getCmpByEntityID<MovementComponent>( enemy_eid );
        auto  new_coords    = enemy_mov_cmp.coords - my_coords;    
        auto  new_dist      = new_coords.length2();

        if(new_dist < dist ) {
            dist = new_dist;
            ai_cmp.target_pos = enemy_mov_cmp.coords;
            ai_cmp.target_ent = enemy_eid;
            result            = true;
        }
    });

    return result;
}

template <typename Context_t> constexpr
bool
AI_System<Context_t>::updatePatrol(Context_t& context, BECS::entID eid) noexcept {
    auto& ai_cmp = context.template getCmpByEntityID<AI_Component>(eid);
    auto& route  = ai_cmp.target_vec;
    auto& index  = ai_cmp.target_index;

    index             = (index+1) % route.size();
    ai_cmp.target_pos = route.at(index);

    return true;
    
}

template <typename Context_t> constexpr
bool
AI_System<Context_t>::updateRoute(Context_t& context, BECS::entID eid) noexcept {
    bool  result { false };

    auto& ai_cmp    = context.template getCmpByEntityID<AI_Component>(eid);
    auto& route     = ai_cmp.target_vec;
    auto& index     = ai_cmp.target_index;
    auto  index_fwd = index + 1;

    if(index_fwd < route.size()) {
        index             = index_fwd;
        result            = true;
        ai_cmp.target_pos = route.at(index);
    }

    return result;
}

} //NS