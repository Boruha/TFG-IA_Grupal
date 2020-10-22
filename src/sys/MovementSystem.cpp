#include <sys/MovementSystem.hpp>
#include <man/Manager_t.hpp>
#include <cmp/MovementComponent.hpp>
#include <utils/AI_Constants.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

void
MovementSystem::init() noexcept { }

bool
MovementSystem::update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept {
    auto& mov_cmp_vec = context->getMovementCmps();

    auto newLocation = [&DeltaTime](std::unique_ptr<MovementComponent>& mov_cmp) {
        mov_cmp->coords.x.number += ENT_MAX_SPEED.getNoScaled() * mov_cmp->dir.x.number * DeltaTime;
        mov_cmp->coords.y.number += ENT_MAX_SPEED.getNoScaled() * mov_cmp->dir.y.number * DeltaTime;    
    };

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), newLocation);

    return true;
}

} //NS