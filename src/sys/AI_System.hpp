#pragma once
#include <sys/System_t.hpp>

#include <utils/Vec2.hpp>

#include <vector>

namespace AIP {

struct Manager_t;
struct Entity_t;
struct AI_Component;
struct MovementComponent;

struct AI_System : System_t {
    explicit  AI_System() = default;

    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept override;

private:
    void arrive(MovementComponent* mov_cmp, const fixed_vec2& target) noexcept;
    void updateTarget(std::unique_ptr<AI_Component>& ai_cmp, MovementComponent* mov_cmp) noexcept;
};


} //NS