#pragma once
#include <cstdint>
#include <utils/ufixed32_t.hpp>

namespace AIP {

//ARRIVE B.
constexpr const fixed32_t ENT_ARRIVE_MIN_DIST   { 10 };
constexpr const fixed32_t ENT_ARRIVE_MIN_DIST2  { ENT_ARRIVE_MIN_DIST * ENT_ARRIVE_MIN_DIST };

constexpr const fixed32_t FLOCK_ARRIVE_MIN_DIST   { 40 };
constexpr const fixed32_t FLOCK_ARRIVE_MIN_DIST2  { FLOCK_ARRIVE_MIN_DIST * FLOCK_ARRIVE_MIN_DIST };

//FLOCKING B. TODO: CALCULAR EL FUNCION DEL TAMAÑO DE LA ENTIDAD.
constexpr const fixed32_t SEPARATION_RAD  { 50 };
constexpr const fixed32_t SEPARATION_RAD2 { SEPARATION_RAD * SEPARATION_RAD };

constexpr const fixed32_t SEPARATION_NUM  { 100000 };

constexpr const fixed32_t COHESION_RAD    { 30 };
constexpr const fixed32_t COHESION_RAD2   { COHESION_RAD * COHESION_RAD };

//MOVEMENT_SYS
constexpr const fixed32_t ENT_MAX_SPEED { 100 };




} //NS