#include <game/sys/AI_System.hpp>

#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/CombatComponent.hpp>
#include <game/cmp/AI_Component.hpp>
#include <game/cmp/TeamComponent.hpp>

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
        auto& ai  = context.template getCmpByEntityID<AI_Component>( eid );
        auto& mov = context.template getCmpByEntityID<MovementComponent>( eid );
        
        decisionMakingIA(context, eid, allies_ids);

        switch (ai.current_behavior) {
            case AI_behaviour::patrol_b : {
                patrol(ai, mov);
                cohesion(context, eid, enemies_ids);
            } break;
        
            case AI_behaviour::chase_b : {
                chase(context, ai, mov);
                cohesion(context, eid, enemies_ids);
            } break;

            case AI_behaviour::attack_b : {
                attack(context, ai, mov);
            } break;

            default: 
                mov.dir.x.number             = mov.dir.y.number             = 0;
                mov.accel_to_target.x.number = mov.accel_to_target.y.number = 0;
            break;
        }
    });

    //update PJ units
    std::for_each(begin(allies_ids), end(allies_ids), [&](BECS::entID eid) {     
        auto& ai  = context.template getCmpByEntityID<AI_Component>( eid );
        auto& mov = context.template getCmpByEntityID<MovementComponent>( eid );

        decisionMakingPJ(context, eid, enemies_ids);

        switch (ai.current_behavior) {
            case AI_behaviour::follow_b : {
                follow(context, ai, mov, allies_ids);
            } break;
        
            case AI_behaviour::chase_b : {
                chase(context, ai, mov);
                cohesion(context, eid, allies_ids);
            } break;

            case AI_behaviour::attack_b : {
                attack(context, ai, mov);
            } break;

            default: {
                mov.dir.x.number             = mov.dir.y.number             = 0;
                mov.accel_to_target.x.number = mov.accel_to_target.y.number = 0;
            } break;
        }
    });

    separation(context, enemies_ids);
    separation(context, allies_ids);
}


/* COMPLEX B. */
template <typename Context_t>
constexpr void
AI_System<Context_t>::patrol(AI_Component& ai, MovementComponent& mov) noexcept {
    if( !arrive(mov, ai.target_pos) ) {
        if( updatePatrol(ai) )
            arrive(mov, ai.target_pos);
    }
}

template <typename Context_t>
constexpr void 
AI_System<Context_t>::chase(Context_t& context, AI_Component& ai, MovementComponent& mov) noexcept {
    auto& mov_target = context.template getCmpByEntityID<MovementComponent>( ai.target_ent );
    ai.target_pos    = mov_target.coords;
    
    if( !arrive(mov, ai.target_pos) ) {
        mov.dir.x.number             = mov.dir.y.number             = 0;
        mov.accel_to_target.x.number = mov.accel_to_target.y.number = 0;
    }
}

template <typename Context_t>
constexpr void
AI_System<Context_t>::attack(Context_t& context, AI_Component& ai, MovementComponent& mov) noexcept {
    auto  eid        = ai.getEntityID();
    auto& mov_target = context.template getCmpByEntityID<MovementComponent>( ai.target_ent );
    auto& combat     = context.template getCmpByEntityID<CombatComponent>( eid );
    ai.target_pos    = mov_target.coords;

    if(combat.current_attack_cd.number <= 0l) {
        combat.current_attack_cd = combat.attack_cd;
        
        switch (combat.attack_range.getNoScaled()) {
            case MEELE_ATK_DIST.getNoScaled(): {
                    auto& eventCmp    = context.template getSCmpByType<EventCmp_t>();
                    eventCmp.attack_msg.emplace_back(eid, ai.target_ent, combat.damage);
                } break;
            
            case RANGE_ATK_DIST.getNoScaled(): {
                    auto& eventCmp    = context.template getSCmpByType<EventCmp_t>();
                    eventCmp.bullet_msg.emplace(eid, mov.orientation, mov.coords.x.getNoScaled(), mov.coords.y.getNoScaled(), combat.team, combat.damage);
                } break;
        }        
    }

    if( !arrive(mov, ai.target_pos, combat.attack_range2,  combat.attack_range2 + 5) ) {
        mov.dir.x.number             = mov.dir.y.number             = 0;
        mov.accel_to_target.x.number = mov.accel_to_target.y.number = 0;
    }
}

template <typename Context_t>
constexpr void 
AI_System<Context_t>::follow(Context_t& context, AI_Component& ai, MovementComponent& mov, std::vector<BECS::entID>& eids) noexcept {
    auto& combat    = context.template getCmpByEntityID<CombatComponent>(   ai.getEntityID()  );
    auto& mov_enemy = context.template getCmpByEntityID<MovementComponent>( ai.target_ent );
    auto& team      = context.template getCmpByEntityID<TeamComponent>(     ai.target_ent );
    auto& targetPos = ai.target_pos;
    
    targetPos = mov_enemy.coords;

    switch ( team.current_form )
    {
        case Formation::no_form : { 
            chase(context, ai, mov);
        } break;
        
        case Formation::ring_form : {
            auto from_centre { mov.coords - targetPos };
            from_centre.normalize();
            targetPos += from_centre * (RING_MAX_DIST - combat.attack_range);

            if( !arrive(mov, targetPos, RING_ARRIVE, RING_ARRIVE) )
                velocity_matching(mov, mov_enemy.dir);

        } break;
    }
}


/* BASIC BEHAVIOURS FUNCTIONS */
template <typename Context_t> 
constexpr void 
AI_System<Context_t>::seek(MovementComponent& mov, fvec2_int& target_pos) noexcept {
    auto target_dir { target_pos - mov.coords };
    
    target_dir.normalize();
    target_dir *= ENT_MAX_SPEED;

    mov.accel_to_target = accelFromDir(target_dir, mov.dir);
}

template <typename Context_t>
constexpr bool
AI_System<Context_t>::arrive(MovementComponent& mov, fvec2_int& target_pos, const fint_t<int64_t> arrive_dist, const fint_t<int64_t> slow_dist) noexcept {
    auto target_dir   { target_pos - mov.coords };
    auto distance2    { target_dir.length2()   };
    auto target_speed = ENT_MAX_SPEED;

    if(distance2 < arrive_dist)
        return false;

    if(distance2 < slow_dist) 
        target_speed *= ( target_dir.length_fix() / ENT_SLOW_DIST );
    
    target_dir.normalize();
    target_dir *= target_speed;

    mov.accel_to_target = accelFromDir(target_dir, mov.dir);

    return true;
}

template <typename Context_t>
constexpr void 
AI_System<Context_t>::velocity_matching(MovementComponent& mov, fvec2_int& target_dir) {
    mov.accel_to_target = accelFromDir(target_dir, mov.dir);
}


/* FLOCKING B. FUNCTIONS */
template <typename Context_t>
constexpr void 
AI_System<Context_t>::separation(Context_t& context, std::vector<BECS::entID>& eids) noexcept {
    auto  end_it  = end(eids);
    
    for(auto ent_it = begin(eids); ent_it<end_it; ++ent_it) {
        auto& mov_cmp   = context.template getCmpByEntityID<MovementComponent>( (*ent_it) );
        auto& sep_force = mov_cmp.separation_force;

        std::for_each(ent_it+1, end_it, [&](BECS::entID ally_eid) {
            auto& ally_mov  = context.template getCmpByEntityID<MovementComponent>( ally_eid );
            auto  diff_vec  { mov_cmp.coords - ally_mov.coords };
            auto  distance2 { diff_vec.length2() };

            if(distance2 < ENT_SEPARATION_DIST2) {
                distance2 *= distance2;
                auto strength { std::min(DECAY_COEFICIENT_SEP / distance2, ENT_MAX_SEP) };
                diff_vec.normalize();
                auto result   { diff_vec * strength };

                sep_force                 += result;
                ally_mov.separation_force += result * -1;
            }
        });

        if(sep_force.length2() > ENT_MAX_SEP) {
            sep_force.normalize();
            sep_force *= ENT_MAX_SEP;
        }

    }// END FOR AI
}

template <typename Context_t>
constexpr void
AI_System<Context_t>::cohesion(Context_t& context, BECS::entID eid_ent, std::vector<BECS::entID>& eids, const fint_t<int64_t> coeficient) noexcept {
    auto& mov_cmp  = context.template getCmpByEntityID<MovementComponent>( eid_ent );
    auto& cohesion = mov_cmp.cohesion_force;

    std::for_each(eids.begin(), eids.end(), [&](BECS::entID ally_eid) {
        if(eid_ent == ally_eid)
            return;
        
        auto& ally_mov = context.template getCmpByEntityID<MovementComponent>( ally_eid );
        auto diff_vec  { ally_mov.coords - mov_cmp.coords };
        auto distance2 { diff_vec.length2() };

        if(distance2 < ENT_COHESION_DIST2) {
            auto strength { std::min(distance2 / coeficient, ENT_MAX_ACCEL) };
            diff_vec.normalize();
            auto result   { diff_vec * strength };

            cohesion += result;
        }
    });

    if(cohesion.length2() > ENT_MAX_ACCEL2) {
        cohesion.normalize();
        cohesion *= ENT_MAX_ACCEL;
    }
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

        if( ai_cmp.target_ent == 0u ) {                 //MUY MEJORABLE !!!=!=!!==!=!=!=!
            curr_behavior     = AI_behaviour::patrol_b;
            ai_cmp.target_pos = ai_cmp.target_vec.at(ai_cmp.target_index);
            return;
        }

        auto& combat_cmp = context.template getCmpByEntityID<CombatComponent>( eid );
        auto  target_dir = ai_cmp.target_pos - mov_cmp.coords;
        auto  distance2  = target_dir.length2();
        
        if( distance2 > VISION_DIST2 ) {
            curr_behavior     = AI_behaviour::patrol_b;
            ai_cmp.target_ent = 0u;
            ai_cmp.target_pos = ai_cmp.target_vec.at(ai_cmp.target_index);
            return;
        }

        if(distance2 < combat_cmp.attack_range2)
            curr_behavior = AI_behaviour::attack_b;
        else
            curr_behavior = AI_behaviour::chase_b;
    }

    if( curr_behavior == AI_behaviour::no_b )
        curr_behavior = AI_behaviour::patrol_b;
}

template <typename Context_t>
constexpr void
AI_System<Context_t>::decisionMakingPJ(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids) noexcept {
    auto& ai     = context.template getCmpByEntityID<AI_Component>( eid );
    auto& curr_b = ai.current_behavior; 

    auto  eidPj = context.template getPlayerID();
    auto& team  = context.template getCmpByEntityID<TeamComponent>( eidPj );
    
    switch (team.action) {
        case AI_behaviour::follow_b : {
                auto& mov = context.template getCmpByEntityID<MovementComponent>( eidPj );
                setFollowing(ai, mov);
                return;
            } break;

        case AI_behaviour::chase_b  : {
                if(curr_b != AI_behaviour::chase_b) {
                    ai.target_ent = 0u;
                    curr_b        = AI_behaviour::chase_b;
                }
            } break;
        
        case AI_behaviour::attack_b : {
            } break;

        case AI_behaviour::patrol_b : {
            } break;

        case AI_behaviour::no_b     : {
            } break;
    }
    
    if( curr_b == AI_behaviour::chase_b || curr_b == AI_behaviour::attack_b ) {
        if( ai.target_ent == 0u ) { 
            if( !findNearEnemy(context, eid, enemy_eids) ) {
                auto& mov = context.template getCmpByEntityID<MovementComponent>( eidPj );
                setFollowing(ai, mov);
                return;
            }
        }

        auto& mov    = context.template getCmpByEntityID<MovementComponent>( eid );
        auto& combat = context.template getCmpByEntityID<CombatComponent>( eid );

        auto target_dir { ai.target_pos - mov.coords };
        auto distance2  { target_dir.length2() };
        
        if(distance2 < combat.attack_range2)
            curr_b = AI_behaviour::attack_b;
        else
            curr_b = AI_behaviour::chase_b;
    
        if( distance2 > VISION_DIST2 ) {
            auto& mov = context.template getCmpByEntityID<MovementComponent>( eidPj );
            setFollowing(ai, mov);
        }
    }

    if( curr_b == AI_behaviour::no_b || curr_b == AI_behaviour::follow_b ) {
        if( !findNearEnemy(context, eid, enemy_eids) ) {
            auto& mov = context.template getCmpByEntityID<MovementComponent>( eidPj );
            setFollowing(ai, mov);
        }
        else
            curr_b = AI_behaviour::chase_b;
    }

}

inline void
setFollowing(AI_Component& ai, MovementComponent& mov) noexcept {
    ai.current_behavior = AI_behaviour::follow_b;
    ai.target_ent       = mov.getEntityID();
    ai.target_pos       = mov.coords;
}


/* AUX FUNCTIONS */
template <typename Context_t> 
constexpr bool 
AI_System<Context_t>::findNearEnemy(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids) noexcept {
    auto& ai  = context.template getCmpByEntityID<AI_Component>( eid );
    auto& mov = context.template getCmpByEntityID<MovementComponent>( eid );
    
    auto& my_coords = mov.coords;
    auto  result    { false };
    auto dist       { VISION_DIST2 };

    std::for_each(begin(enemy_eids), end(enemy_eids), [&](BECS::entID enemy_eid) {
        auto& enemy_mov  = context.template getCmpByEntityID<MovementComponent>( enemy_eid );
        auto  new_coords = enemy_mov.coords - my_coords;    
        auto  new_dist   = new_coords.length2();

        if(new_dist < dist ) {
            dist   = new_dist;
            result = true;
            ai.target_pos = enemy_mov.coords;
            ai.target_ent = enemy_eid;
        }
    });

    return result;
}

inline bool
updatePatrol(AI_Component& ai) noexcept {
    auto& route  = ai.target_vec;
    auto& index  = ai.target_index;

    index         = (index+1) % route.size();
    ai.target_pos = route.at(index);

    return true;
}

inline bool
updateRoute(AI_Component& ai) noexcept {
    bool  result { false };

    auto& route     = ai.target_vec;
    auto& index     = ai.target_index;
    auto  index_fwd = index + 1;

    if( index_fwd < route.size() ) {
        index         = index_fwd;
        result        = true;
        ai.target_pos = route.at(index);
    }

    return result;
}


inline fvec2<fint_t<int64_t>> 
accelFromDir(fvec2<fint_t<int64_t>> target_dir, fvec2<fint_t<int64_t>> my_dir) noexcept {
    auto my_accel  { target_dir - my_dir };
         my_accel /= ENT_TIME_TO_TARGET;

    if(my_accel.length2() > ENT_MAX_ACCEL2) {
        my_accel.normalize();
        my_accel *= ENT_MAX_ACCEL;
    }

    return my_accel;
}


} //NS