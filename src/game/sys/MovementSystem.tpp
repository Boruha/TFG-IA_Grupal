#include <game/sys/MovementSystem.hpp>
#include <game/sys/AI_System.hpp>
#include <game/utils/AI_Constants.hpp>
#include <game/utils/ScreenData.hpp>

#include <algorithm>

namespace AIP {

template <typename Context_t>
void
MovementSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& movCmps = context.template getComponentVector<MovementComponent>();

    moveCamera(context);

    std::for_each(begin(movCmps), end(movCmps),
        [&](MovementComponent& mov) { moveEntity(mov, DeltaTime); });
    
}

template <typename Context_t>
void
MovementSystem<Context_t>::moveEntity(MovementComponent& mov, const fint_t<int64_t> DeltaTime) noexcept {
    auto& dir = mov.dir;
    auto& acc = mov.accel_to_target;
    auto& sep = mov.separation_force;
    auto& coh = mov.cohesion_force;

    dir += acc; dir += sep; dir += coh;

    if(dir.length2() > ENT_MAX_SPEED2) {
        dir.normalize();
        dir *= ENT_MAX_SPEED;
    }

    mov.coords += dir * DeltaTime;

    /* resets */
    mov.acc_copy_to_draw = std::move(acc);
    mov.sep_copy_to_draw = std::move(sep);
    mov.coh_copy_to_draw = std::move(coh);

    acc.setZero(); sep.setZero(); coh.setZero();
}

template <typename Context_t>
void
MovementSystem<Context_t>::moveCamera(Context_t& context) noexcept {
    auto  camID  = context.getCameraID();
    auto& camMov = context.template getCmpByEntityID<MovementComponent>(camID);
    auto& pjMov  = context.template getCmpByEntityID<MovementComponent>( context.getPlayerID() );
    auto& camC2D = context.template getCmpByEntityID<Collider2DCmp>(camID);

    auto target_pos { pjMov.coords - (camC2D.p2/2l) };

    arrive(camMov, target_pos);

}

} //NS