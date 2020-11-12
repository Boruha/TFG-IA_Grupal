#pragma once
#include <cstdint>
#include <utils/ufixed32_t.hpp>

namespace AIP {

//ARRIVE B.
constexpr fixed32_t ENT_ARRIVE_MIN_DIST   { 15 };
constexpr fixed32_t ENT_ARRIVE_MIN_DIST2  { ENT_ARRIVE_MIN_DIST * ENT_ARRIVE_MIN_DIST };

//EVADE & FLEE BEHAVIOUR
constexpr fixed32_t ENT_ESCAPE_MAX_DIST   { 400 };
constexpr fixed32_t ENT_ESCAPE_MAX_DIST2  { ENT_ESCAPE_MAX_DIST * ENT_ESCAPE_MAX_DIST };

//SEPARATION B. TODO: CALCULAR EL FUNCION DEL TAMAÑO DE LA ENTIDAD.
constexpr fixed32_t SEPARATION_RAD  { 5 };
constexpr fixed32_t SEPARATION_RAD2 { SEPARATION_RAD * SEPARATION_RAD };

constexpr fixed32_t SEPARATION_NUM  { 100000 };

//MOVEMENT_SYS
constexpr int32_t    ENT_MAX_SPEED_NS { 1 };
constexpr fixed32_t  ENT_MAX_SPEED    { ENT_MAX_SPEED_NS };

} //NS