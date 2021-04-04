#pragma once
#include <game/utils/fvec2.hpp>
#include <game/utils/AI_Constants.hpp>

#include <ecs/utils/Alias.hpp>

#include <vector>

namespace AIP {

struct AI_Component;
struct MovementComponent;

template <typename Context_t>
struct AI_System {
    using fvec2_int = fvec2<fint_t<int64_t>>;

    void init() noexcept;
    void update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;

private:
/* CONPLEX B. */
    constexpr void patrol(AI_Component& ai, MovementComponent& mov) noexcept;
    constexpr void chase( Context_t& context, AI_Component& ai, MovementComponent& mov) noexcept;
    constexpr void attack(Context_t& context, AI_Component& ai, MovementComponent& mov) noexcept;
    constexpr void follow(Context_t& context, AI_Component& ai, MovementComponent& mov, std::vector<BECS::entID>& eids) noexcept;
                                              
/* FLOCKING B. COMPO */
    constexpr void separation(Context_t& context, std::vector<BECS::entID>& eids) noexcept;
    constexpr void cohesion(  Context_t& context, BECS::entID eid_ent, std::vector<BECS::entID>& eids, const fint_t<int64_t> coeficient = DECAY_COEFICIENT_COH) noexcept;

/* DECISION FUNCTIONS */
    constexpr void decisionMakingIA(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids) noexcept;
    constexpr void decisionMakingPJ(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids) noexcept;

/* AUX */
    constexpr bool findNearEnemy(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids) noexcept;
};


void setFollowing(AI_Component& ai, MovementComponent& mov) noexcept;
void setPatroling(AI_Component& ai) noexcept;
bool updatePatrol(AI_Component& ai) noexcept;
bool updateRoute( AI_Component& ai) noexcept;

fvec2<fint_t<int64_t>> accelFromDir(fvec2<fint_t<int64_t>> target_dir, fvec2<fint_t<int64_t>> my_dir) noexcept;

/* STEERING B. BASIC */
void seek(MovementComponent& mov, fvec2<fint_t<int64_t>>& target_pos) noexcept;
bool arrive(MovementComponent& mov, fvec2<fint_t<int64_t>>& target_pos, const fint_t<int64_t> arrive_dist = ENT_ARRIVE_DIST2, const fint_t<int64_t> slow_dist = ENT_SLOW_DIST2) noexcept;
void velocity_matching(MovementComponent& mov, fvec2<fint_t<int64_t>>& target_dir) noexcept;
void face(MovementComponent& mov, fvec2<fint_t<int64_t>>& target_dir) noexcept;

} //NS

/*
    auto& ai_cmp = context.template getCmpByEntityID<AI_Component>( eid );
    auto& team   = context.template getCmpByEntityID<TeamComponent>( context.template getPlayerID() );
    auto comand  = team.action;

    auto& curr_behavior = ai_cmp.current_behavior;

    if( curr_behavior == AI_behaviour::chase_b || curr_behavior == AI_behaviour::attack_b ) {

        if( ai_cmp.target_ent == 0u ) {                 //MUY MEJORABLE !!!=!=!!==!=!=!=!
            auto  pj_eid  = context.template getPlayerID();
            auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>( pj_eid );

            curr_behavior     = AI_behaviour::follow_b;
            ai_cmp.target_ent = pj_eid;
            ai_cmp.target_pos = mov_cmp.coords;
            return;
        }

        auto& mov_cmp    = context.template getCmpByEntityID<MovementComponent>( eid );
        auto& combat_cmp = context.template getCmpByEntityID<CombatComponent>( eid );

        auto  target_dir = ai_cmp.target_pos - mov_cmp.coords;
        auto  distance2  = target_dir.length2();
        
        if(distance2 < combat_cmp.attack_range2)
            comand = AI_behaviour::attack_b;
        else
            comand = AI_behaviour::chase_b;
    
        if( distance2 > VISION_DIST2 )
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
*/
