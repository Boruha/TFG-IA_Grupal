#include <game/sys/MovementSystem.hpp>
#include <game/utils/AI_Constants.hpp>

#include <algorithm>

namespace AIP {

template <typename Context_t>
void
MovementSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& mov_cmp_vec = context.template getComponentVector<MovementComponent>();

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), 
        [&](MovementComponent& mov_cmp) {
            mov_cmp.dir += mov_cmp.accel_to_target;
            mov_cmp.dir += mov_cmp.separation_force;
            mov_cmp.dir += mov_cmp.cohesion_force;
    
            if(mov_cmp.dir.length2() > ENT_MAX_SPEED2) {
                mov_cmp.dir.normalize();
                mov_cmp.dir *= ENT_MAX_SPEED;
            }
    
            mov_cmp.coords += mov_cmp.dir * DeltaTime;

            /* resets */
            mov_cmp.sep_copy_to_draw = std::move(mov_cmp.separation_force);
            mov_cmp.coh_copy_to_draw = std::move(mov_cmp.cohesion_force);
    });
    
}

} //NS