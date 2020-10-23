#pragma once
#include <cstdint>
#include <utils/ufixed32_t.hpp>

namespace AIP {

//ARRIVE B.
constexpr fixed32_t ENT_ARRIVE_MIN_DIST   { 20 };
constexpr fixed32_t ENT_ARRIVE_MIN_DIST2  { ENT_ARRIVE_MIN_DIST * ENT_ARRIVE_MIN_DIST };

constexpr fixed32_t FLOCK_ARRIVE_MIN_DIST   { 80 };
constexpr fixed32_t FLOCK_ARRIVE_MIN_DIST2  { FLOCK_ARRIVE_MIN_DIST * FLOCK_ARRIVE_MIN_DIST };

//FLOCKING B. TODO: CALCULAR EL FUNCION DEL TAMAÑO DE LA ENTIDAD.
constexpr fixed32_t SEPARATION_RAD  { 70 };
constexpr fixed32_t SEPARATION_RAD2 { SEPARATION_RAD * SEPARATION_RAD };

constexpr fixed32_t SEPARATION_NUM  { 100000 };

constexpr fixed32_t COHESION_RAD    { 50 };
constexpr fixed32_t COHESION_RAD2   { COHESION_RAD * COHESION_RAD };

//MOVEMENT_SYS
constexpr fixed32_t  ENT_MAX_SPEED  { 300 };
constexpr int32_t    ACCEL_MODIFIER { 8 };




} //NS