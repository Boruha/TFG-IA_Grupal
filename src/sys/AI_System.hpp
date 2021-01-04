#pragma once
#include <sys/System_t.hpp>

#include <utils/Vec2.hpp>

#include <vector>
#include <optional>
#include <functional>

namespace AIP {

struct Manager_t;
struct AI_Component;
struct MovementComponent;

struct AI_System : System_t {
    using optVec2_refw   = std::optional<std::reference_wrapper<fixed_vec2>>;
    explicit AI_System() = default;

    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept override;

private:
/* CONPLEX B. */
    void patrol(AI_Component& ai_cmp  , MovementComponent* mov_cmp) noexcept;
    void chase(AI_Component& ai_cmp   , MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept;
    void run_away(AI_Component& ai_cmp, MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept;
    void pursue(AI_Component& ai_cmp  , MovementComponent* mov_cmp, MovementComponent* target_mov_cmp) noexcept;
    void evade(AI_Component& ai_cmp   , MovementComponent* mov_cmp, MovementComponent* target_mov_cmp) noexcept;
    void attack(AI_Component& ai_cmp  , MovementComponent* mov_cmp, fixed_vec2& target_pos, const std::unique_ptr<Manager_t>& context) noexcept;
                                              
/* STEERING B. BASIC */
    bool arrive(MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept;
    bool leave(MovementComponent* mov_cmp, fixed_vec2& target_pos) noexcept;

/* FLOCKING B. COMPO */
    void separation(const std::unique_ptr<Manager_t>& context, std::vector<AI_Component>& AI_cmps) noexcept;
    void cohesion(const std::unique_ptr<Manager_t>& context, std::vector<AI_Component>& AI_cmps) noexcept;

/* AUX */
    [[nodiscard]] optVec2_refw updatePatrol(AI_Component& ai_cmp) noexcept;
    [[nodiscard]] optVec2_refw updateRoute(AI_Component& ai_cmp) noexcept;
};

/* Adiciones futuras */
    //pathfinding / pathfollowing
    //obstacle avoidance
    //wander
    //direction aligment

} //NS