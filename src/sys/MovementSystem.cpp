#include <sys/MovementSystem.hpp>
#include <man/Manager_t.hpp>
#include <cmp/MovementComponent.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

void
MovementSystem::init() noexcept { }

bool
MovementSystem::update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept {
    auto& mov_cmp_vec = context->getMovementCmps();

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), 
        [&](std::unique_ptr<MovementComponent>& mov_cmp) {
            //aplicar los distintos modificadores
            mov_cmp->dir += mov_cmp->accel_to_target;
            mov_cmp->dir += mov_cmp->separation_force;
    
            //nos aseguramos de no pasarnos de la vel max.
            if(mov_cmp->dir.length2() > ENT_MAX_SPEED2) {
                mov_cmp->dir.normalize();
                mov_cmp->dir *= ENT_MAX_SPEED;
            }
    
            //calcular la nueva posicion
            mov_cmp->coords += mov_cmp->dir * DeltaTime;
            
            /* resets */
            mov_cmp->copy_to_draw = mov_cmp->separation_force;
            mov_cmp->separation_force.x.number = mov_cmp->separation_force.y.number = 0;
    });
        
    return true;
}

} //NS