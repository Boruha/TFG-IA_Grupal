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

#pragma once
#include <game/utils/fvec2.hpp>

#include <ecs/utils/Alias.hpp>
#include <game/utils/GameConditions.hpp>

#include <vector>

namespace AIP {

struct MovementComponent;

template <typename Context_t>
struct CollisionSystem {
    GameConditions update(Context_t& context) noexcept;

private:
    GameConditions checkTriggerBoxes(Context_t& context) noexcept; 

    void checkWorldLimits(Context_t& context, std::vector<MovementComponent>& movCmps) noexcept;
    void bulletsCollision(Context_t& context, std::vector<BECS::entID>& team, std::vector<BECS::entID>& bullets) noexcept;
};

} // NS
