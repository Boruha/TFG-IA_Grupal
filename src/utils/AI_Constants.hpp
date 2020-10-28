#pragma once
#include <cstdint>
#include <utils/ufixed32_t.hpp>

namespace AIP {

//ARRIVE B.
constexpr fixed32_t ENT_ARRIVE_MIN_DIST   { 10 };
constexpr fixed32_t ENT_ARRIVE_MIN_DIST2  { ENT_ARRIVE_MIN_DIST * ENT_ARRIVE_MIN_DIST };

constexpr fixed32_t ENT_DECELERATE_MIN_DIST   { 36 };
constexpr fixed32_t ENT_DECELERATE_MIN_DIST2  { ENT_DECELERATE_MIN_DIST * ENT_DECELERATE_MIN_DIST };

constexpr fixed32_t FLOCK_ARRIVE_MIN_DIST   { 30 };
constexpr fixed32_t FLOCK_ARRIVE_MIN_DIST2  { FLOCK_ARRIVE_MIN_DIST * FLOCK_ARRIVE_MIN_DIST };

//FLOCKING B. TODO: CALCULAR EL FUNCION DEL TAMAÑO DE LA ENTIDAD.
constexpr fixed32_t SEPARATION_RAD  { 70 };
constexpr fixed32_t SEPARATION_RAD2 { SEPARATION_RAD * SEPARATION_RAD };

constexpr fixed32_t SEPARATION_NUM  { 100000 };

constexpr fixed32_t COHESION_RAD    { 40 };
constexpr fixed32_t COHESION_RAD2   { COHESION_RAD * COHESION_RAD };

//MOVEMENT_SYS
constexpr int32_t    ENT_MAX_SPEED_NS { 200 };
constexpr fixed32_t  ENT_MAX_SPEED    { ENT_MAX_SPEED_NS };
constexpr int32_t    ACCEL_MODIFIER   { 8 };
constexpr fixed32_t  ROTATION_CAP     { 0.2f };




} //NS