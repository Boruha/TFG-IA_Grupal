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
    using fvec2_int = fvec2<fint_t<int64_t>>;

    void init() noexcept;
    void update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;

private:
/* CONPLEX B. */
    constexpr void patrol(AI_Component& ai, MovementComponent& mov) noexcept;
    constexpr void chase( Context_t& context, AI_Component& ai, MovementComponent& mov) noexcept;
    constexpr void attack(Context_t& context, AI_Component& ai, MovementComponent& mov) noexcept;
    constexpr void follow(Context_t& context, AI_Component& ai, MovementComponent& mov, std::vector<BECS::entID>& eids) noexcept;
                                              
/* STEERING B. BASIC */
    constexpr void seek(MovementComponent& mov, fvec2_int& target_pos) noexcept;
    constexpr bool arrive(MovementComponent& mov, fvec2_int& target_pos, const fint_t<int64_t> arrive_dist = ENT_ARRIVE_DIST2, const fint_t<int64_t> slow_dist = ENT_SLOW_DIST2) noexcept;
    constexpr void velocity_matching(MovementComponent& mov, fvec2_int& target_dir);

/* FLOCKING B. COMPO */
    constexpr void separation(Context_t& context, std::vector<BECS::entID>& eids) noexcept;
    constexpr void cohesion(  Context_t& context, BECS::entID eid_ent, std::vector<BECS::entID>& eids, const fint_t<int64_t> coeficient = DECAY_COEFICIENT_COH) noexcept;

/* DECISION FUNCTIONS */
    constexpr void decisionMakingIA(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids) noexcept;
    constexpr void decisionMakingPJ(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids, AI_behaviour comand) noexcept;

/* AUX */
    constexpr bool findNearEnemy(Context_t& context, BECS::entID eid, std::vector<BECS::entID>& enemy_eids) noexcept;
    constexpr bool updatePatrol( AI_Component& ai) noexcept;
    constexpr bool updateRoute(  AI_Component& ai) noexcept;

    constexpr fvec2_int accelFromDir(fvec2_int target_dir, fvec2_int my_dir) noexcept;
};

/* Adiciones futuras posibles */
    //pathfinding / pathfollowing
    //obstacle avoidance
    //wander
    //direction aligment

} //NS
