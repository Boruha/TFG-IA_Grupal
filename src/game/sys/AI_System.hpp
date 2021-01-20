#pragma once
#include <game/utils/EventHandler.hpp>
#include <game/utils/fvec2.hpp>

#include <vector>
#include <optional>
#include <functional>

namespace AIP {

struct AI_Component;
struct MovementComponent;

template <typename Context_t>
struct AI_System : EventHandler {
    using optVec2_refw = std::optional<std::reference_wrapper< fvec2< fint_t<int64_t> >  >>;

    void init() noexcept;
    bool update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;

private:
/* CONPLEX B. */
    void patrol(AI_Component& ai_cmp  , MovementComponent& mov_cmp) noexcept;
    void chase(MovementComponent& mov_cmp, fvec2<fint_t<int64_t>>& target_pos) noexcept;
    void run_away(MovementComponent& mov_cmp, fvec2<fint_t<int64_t>>& target_pos) noexcept;
    void pursue(MovementComponent& mov_cmp, MovementComponent& target_mov_cmp) noexcept;
    void evade(MovementComponent& mov_cmp, MovementComponent& target_mov_cmp) noexcept;
    void attack(MovementComponent& mov_cmp, fvec2<fint_t<int64_t>>& target_pos, Context_t& context) noexcept;
                                              
/* STEERING B. BASIC */
    bool arrive(MovementComponent& mov_cmp, fvec2<fint_t<int64_t>>& target_pos) noexcept;
    bool leave( MovementComponent& mov_cmp, fvec2<fint_t<int64_t>>& target_pos) noexcept;

/* FLOCKING B. COMPO */
    void separation(Context_t& context) noexcept;
    void cohesion(  Context_t& context, std::vector<BECS::entID>& eids) noexcept;

/* AUX */
    [[nodiscard]] optVec2_refw updatePatrol(AI_Component& ai_cmp) noexcept;
    [[nodiscard]] optVec2_refw updateRoute(AI_Component& ai_cmp) noexcept;
};

/* Adiciones futuras posibles */
    //pathfinding / pathfollowing
    //obstacle avoidance
    //wander
    //direction aligment

} //NS