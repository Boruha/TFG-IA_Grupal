#include <sys/MovementSystem.hpp>
#include <man/Manager_t.hpp>
#include <cmp/MovementComponent.hpp>

#include <algorithm>

namespace AIP {

void
MovementSystem::init() noexcept { }

bool
MovementSystem::update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept {
    auto& mov_cmp_vec = context->getMovementCmps();

    auto newLocation = [&](std::unique_ptr<MovementComponent>& mov_cmp) {
        mov_cmp->vel = ENT_MAX_SPEED;
        mov_cmp->coords += mov_cmp->dir * DeltaTime * mov_cmp->vel;
    };

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), newLocation);

    return true;
}

} //NS