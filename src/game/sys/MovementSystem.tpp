#include <game/sys/MovementSystem.hpp>
#include <game/utils/AI_Constants.hpp>

#include <algorithm>

namespace AIP {

template <typename Context_t>
bool
MovementSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& mov_cmp_vec = context.template getComponentVector<MovementComponent>();

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), 
        [&](MovementComponent& mov_cmp) {
            //aplicar los distintos modificadores
            mov_cmp.dir += mov_cmp.accel_to_target;
            mov_cmp.dir += mov_cmp.separation_force;
            mov_cmp.dir += mov_cmp.cohesion_force;
    
            //nos aseguramos de no pasarnos de la vel max.
            if(mov_cmp.dir.length2() > ENT_MAX_SPEED2) {
                mov_cmp.dir.normalize();
                mov_cmp.dir *= ENT_MAX_SPEED;
            }
    
            //calcular la nueva posicion
            mov_cmp.coords += mov_cmp.dir * DeltaTime;

            /* resets */
            mov_cmp.sep_copy_to_draw = mov_cmp.separation_force;
            mov_cmp.coh_copy_to_draw = mov_cmp.cohesion_force;

            mov_cmp.separation_force.x.number = mov_cmp.separation_force.y.number = 0;
            mov_cmp.cohesion_force.x.number   = mov_cmp.cohesion_force.y.number   = 0;
            mov_cmp.cohesion_count.number     = 0;
    });
        
    return true;
}

} //NS