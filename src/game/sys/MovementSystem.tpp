#include <game/sys/MovementSystem.hpp>
#include <game/utils/AI_Constants.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

template <typename Context_t>
void
MovementSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& mov_cmp_vec = context.template getComponentVector<MovementComponent>();

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), 
        [&](MovementComponent& mov_cmp) {
            auto& dir = mov_cmp.dir;
            
            dir += mov_cmp.accel_to_target;
            dir += mov_cmp.separation_force;
            dir += mov_cmp.cohesion_force;
    
            if(dir.length2() > ENT_MAX_SPEED2) {
                dir.normalize();
                dir *= ENT_MAX_SPEED;
            }
    
            mov_cmp.coords += dir * DeltaTime;

            if(dir.length_fix() > EPSILON)
                mov_cmp.orientation = dir;

            /* resets */
            mov_cmp.acc_copy_to_draw = std::exchange(mov_cmp.accel_to_target, 0l);
            mov_cmp.sep_copy_to_draw = std::exchange(mov_cmp.separation_force, 0l);
            mov_cmp.coh_copy_to_draw = std::exchange(mov_cmp.cohesion_force, 0l);
    });
    
}

} //NS