#pragma once
#include <sys/System_t.hpp>

#include <utils/AI_Constants.hpp>

#include <memory>

namespace AIP {

struct Manager_t;
struct MovementComponent;

struct MovementSystem : System_t {
    explicit MovementSystem() = default;
    
    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept override;

private:
    void calculeCurrentVelocity(fixed32_t& current_vel, fixed32_t dir_length, bool in_mov) noexcept;
};

} //NS
