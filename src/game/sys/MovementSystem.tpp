/*
Copyright (C) <2020-2021> Borja Pozo Wals (Tw: @Chico_Riot | GitHub: Boruha)

This file is part of 'TFG: Gestión y manejo de comportamientos grupales 
de entidades en videojuegos'.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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