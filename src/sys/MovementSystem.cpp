#include <sys/MovementSystem.hpp>
#include <man/Manager_t.hpp>
#include <cmp/MovementComponent.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

void
MovementSystem::init() noexcept { }

bool
MovementSystem::update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept {
    auto& mov_cmp_vec = context->getMovementCmps();

    auto newLocation = [&](std::unique_ptr<MovementComponent>& mov_cmp) {
        auto& current_v   = mov_cmp->current_vel.number;
        auto& current_dir = mov_cmp->dir;

        //cambiar como gestiono la aceleración
        if( current_dir.length2().number != 0 )
            current_v = std::clamp((mov_cmp->Accel_mod * ACCEL_MODIFIER) + current_v, 0, ENT_MAX_SPEED_NS);
        else
            current_v = std::clamp(current_v/2, 0, ENT_MAX_SPEED_NS);

        current_dir.normalize();

        mov_cmp->coords.x.number += current_v * current_dir.x.number * DeltaTime;
        mov_cmp->coords.y.number += current_v * current_dir.y.number * DeltaTime;
    };
    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), newLocation);

    return true;
}

} //NS