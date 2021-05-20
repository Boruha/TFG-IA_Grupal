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
#include <game/utils/fint_t.hpp>

namespace AIP {

//EXTRA
constexpr fint_t<int64_t> EPSILON       { 15l };
constexpr fint_t<int64_t> RING_ARRIVE   { 50l };
constexpr fint_t<int64_t> SLOW_RING     { RING_ARRIVE + 5l };
constexpr fint_t<int64_t> RING_MAX_DIST { 220l };

//SENSOR
constexpr fint_t<int64_t> VISION_DIST     { 180l };
constexpr fint_t<int64_t> VISION_DIST2    { VISION_DIST * VISION_DIST };
constexpr fint_t<int64_t> MEELE_ATK_DIST  { 50l };
constexpr fint_t<int64_t> MEELE_ATK_DIST2 { MEELE_ATK_DIST * MEELE_ATK_DIST };
constexpr fint_t<int64_t> RANGE_ATK_DIST  { 160l };
constexpr fint_t<int64_t> RANGE_ATK_DIST2 { RANGE_ATK_DIST * RANGE_ATK_DIST };

//ARRIVE B.
constexpr fint_t<int64_t> ENT_ARRIVE_DIST    { 60l };
constexpr fint_t<int64_t> ENT_ARRIVE_DIST2   { ENT_ARRIVE_DIST * ENT_ARRIVE_DIST };
constexpr fint_t<int64_t> ENT_SLOW_DIST      { ENT_ARRIVE_DIST + 30l };
constexpr fint_t<int64_t> ENT_SLOW_DIST2     { ENT_SLOW_DIST * ENT_SLOW_DIST };
constexpr fint_t<int64_t> ENT_TIME_TO_TARGET { 1.2f };

//SEPARATION B.
constexpr fint_t<int64_t> ENT_SEPARATION_DIST  { 200l };
constexpr fint_t<int64_t> ENT_SEPARATION_DIST2 { ENT_SEPARATION_DIST * ENT_SEPARATION_DIST };
constexpr fint_t<int64_t> DECAY_COEFICIENT_SEP { 8000000l };
constexpr fint_t<int64_t> ENT_MAX_SEP          { 100l };

//COHESION B.
constexpr fint_t<int64_t> ENT_COHESION_DIST    { 150l };
constexpr fint_t<int64_t> ENT_COHESION_DIST2   { ENT_COHESION_DIST * ENT_COHESION_DIST };
constexpr fint_t<int64_t> DECAY_COEFICIENT_COH { 3000l };
constexpr fint_t<int64_t> DECAY_SOFT_COEFT_COH { 6000l };

//MOVEMENT_SYS
constexpr fint_t<int64_t> ENT_MAX_SPEED  { 280l };
constexpr fint_t<int64_t> ENT_MAX_SPEED2 { ENT_MAX_SPEED * ENT_MAX_SPEED };

constexpr fint_t<int64_t> ENT_MAX_ACCEL  { 15l };
constexpr fint_t<int64_t> ENT_MAX_ACCEL2 { ENT_MAX_ACCEL * ENT_MAX_ACCEL };

//FLEE B.
//constexpr fint_t<int64_t> ENT_FLEE_DIST  { 600l };
//constexpr fint_t<int64_t> ENT_FLEE_DIST2 { ENT_FLEE_DIST * ENT_FLEE_DIST };

//constexpr fint_t<int64_t> ENT_FAR_SLOW_DIST  { 595l };
//constexpr fint_t<int64_t> ENT_FAR_SLOW_DIST2 { ENT_FAR_SLOW_DIST * ENT_FAR_SLOW_DIST };


} //NS