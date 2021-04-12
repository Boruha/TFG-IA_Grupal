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

fvec2<fint_t<int64_t>> accelFromDir(fvec2<fint_t<int64_t>> target_dir, fvec2<fint_t<int64_t>> my_dir) noexcept;

/* STEERING B. BASIC */
void seek(MovementComponent& mov, fvec2<fint_t<int64_t>>& target_pos) noexcept;
bool arrive(MovementComponent& mov, fvec2<fint_t<int64_t>>& target_pos, const fint_t<int64_t> arrive_dist = ENT_ARRIVE_DIST2, const fint_t<int64_t> slow_dist = ENT_SLOW_DIST2) noexcept;
void velocity_matching(MovementComponent& mov, fvec2<fint_t<int64_t>>& target_dir) noexcept;
void face(MovementComponent& mov, fvec2<fint_t<int64_t>>& target_dir) noexcept;

} //NS