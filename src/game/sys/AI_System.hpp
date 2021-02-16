#pragma once
#include <game/utils/EventHandler.hpp>
#include <game/utils/fvec2.hpp>
#include <game/cmp/AI_Component.hpp>
#include <game/utils/AI_Constants.hpp>

#include <vector>

namespace AIP {

struct AI_Component;
struct MovementComponent;

template <typename Context_t>
struct AI_System : EventHandler {

    void init() noexcept;
    void update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;

private:
/* CONPLEX B. */
    constexpr void patrol(Context_t& context, BECS::entID eid) noexcept;
    constexpr void chase( Context_t& context, BECS::entID eid) noexcept;
    constexpr void attack(Context_t& context, BECS::entID eid) noexcept;
                                              
/* STEERING B. BASIC */
    constexpr bool arrive(Context_t& context, BECS::entID eid, const fint_t<int64_t> arrive_dist = ENT_ARRIVE_DIST2, const fint_t<int64_t> slow_dist = ENT_SLOW_DIST2) noexcept;

/* FLOCKING B. COMPO */
    constexpr void separation(Context_t& context, std::vector<BECS::entID>& eids) noexcept;
    constexpr void cohesion(  Context_t& context, BECS::entID eid_ent, std::vector<BECS::entID>& eids) noexcept;

/* DECISION FUNCTIONS */
    constexpr void decisionMakingIA(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids) noexcept;
    constexpr void decisionMakingPJ(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids, AI_behaviour comand) noexcept;

/* AUX */
    constexpr bool findNearEnemy(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids) noexcept;
    constexpr bool updatePatrol( Context_t& context, BECS::entID eid) noexcept;
    constexpr bool updateRoute(  Context_t& context, BECS::entID eid) noexcept;
};

/* Adiciones futuras posibles */
    //pathfinding / pathfollowing
    //obstacle avoidance
    //wander
    //direction aligment

} //NS


/*
    constexpr void run_away(Context_t& context, BECS::entID eid) noexcept;
    constexpr void pursue(  Context_t& context, BECS::entID eid) noexcept;
    constexpr void evade(   Context_t& context, BECS::entID eid) noexcept;
    constexpr bool leave( Context_t& context, BECS::entID eid) noexcept;

*/