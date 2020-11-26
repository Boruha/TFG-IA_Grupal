#pragma once
#include <sys/System_t.hpp>

#include <utils/Vec2.hpp>

#include <vector>
#include <optional>
#include <functional>

namespace AIP {

struct Manager_t;
struct Entity_t;
struct AI_Component;
struct MovementComponent;

struct AI_System : System_t {
    using optVec2_refw = std::optional<std::reference_wrapper<fixed_vec2>>;

    explicit AI_System() = default;

    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept override;

private:
    /* Steering B. */
    void arrive(MovementComponent* mov_cmp, std::unique_ptr<AI_Component>& ai_cmp) noexcept;
    
    /* FLOCKING B. FUNCTIONS */
    void separation(const std::unique_ptr<Manager_t>& context, std::vector<std::unique_ptr<AI_Component>>& AI_cmps) noexcept;

    /* AUX */
    [[nodiscard]] optVec2_refw updateTarget(std::unique_ptr<AI_Component>& ai_cmp) noexcept;
};


} //NS