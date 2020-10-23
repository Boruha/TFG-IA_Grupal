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
        mov_cmp->dir.x = mov_cmp->target.x + mov_cmp->cohesion.x + mov_cmp->separation.x;
        mov_cmp->dir.y = mov_cmp->target.y + mov_cmp->cohesion.y + mov_cmp->separation.y;

        calculeCurrentVelocity(mov_cmp->current_vel, mov_cmp->dir.length2(), mov_cmp->in_movement);

        mov_cmp->dir.normalize();

        //mov_cmp->coords.x.number += ENT_MAX_SPEED.getNoScaled() * mov_cmp->dir.x.number * DeltaTime;
        //mov_cmp->coords.y.number += ENT_MAX_SPEED.getNoScaled() * mov_cmp->dir.y.number * DeltaTime;

        std::cout << "out calcule " << mov_cmp->current_vel.number << "\n";

        std::cout << "coordx: " << mov_cmp->coords.x.number << "\t";
        std::cout << "coordy: " << mov_cmp->coords.y.number << "\n";
        
        mov_cmp->coords.x.number += mov_cmp->current_vel.number * mov_cmp->dir.x.number * DeltaTime;
        mov_cmp->coords.y.number += mov_cmp->current_vel.number * mov_cmp->dir.y.number * DeltaTime;

        std::cout << "coordx: " << mov_cmp->coords.x.number << "\t";
        std::cout << "coordy: " << mov_cmp->coords.y.number << "\n\n";
        
        std::cout << "resultx: " << mov_cmp->current_vel.number << " * " <<  mov_cmp->dir.x.number << "\t";
        std::cout << "resulty: " << mov_cmp->current_vel.number << " * " <<  mov_cmp->dir.y.number << "\n\n";

    };
    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), newLocation);

    return true;
}

void
MovementSystem::calculeCurrentVelocity(fixed32_t& current_vel, fixed32_t dir_length, bool in_mov) noexcept {
    if(dir_length > 0) {
        current_vel.number += ACCEL_MODIFIER;
        
        if(current_vel.number > ENT_MAX_SPEED.getNoScaled())
            current_vel.number = ENT_MAX_SPEED.getNoScaled();
    } else
    {
        current_vel.number = 0;
    }
}


} //NS