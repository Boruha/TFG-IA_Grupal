#pragma once
#include <cstdint>
#include <utils/ufixed64_t.hpp>

namespace AIP {

//ARRIVE B.
constexpr fixed64_t ENT_ARRIVE_MIN_DIST   { 15l };
constexpr fixed64_t ENT_ARRIVE_MIN_DIST2  { ENT_ARRIVE_MIN_DIST * ENT_ARRIVE_MIN_DIST };

//EVADE & FLEE BEHAVIOUR
constexpr fixed64_t ENT_ESCAPE_MAX_DIST   { 1l };
constexpr fixed64_t ENT_ESCAPE_MAX_DIST2  { ENT_ESCAPE_MAX_DIST * ENT_ESCAPE_MAX_DIST };

//SEPARATION B. TODO: CALCULAR EL FUNCION DEL TAMAÑO DE LA ENTIDAD.
constexpr fixed64_t SEPARATION_RAD  { 1l };
constexpr fixed64_t SEPARATION_RAD2 { SEPARATION_RAD * SEPARATION_RAD };
constexpr fixed64_t SEPARATION_NUM  { 1l };

//MOVEMENT_SYS
constexpr int64_t    ENT_MAX_SPEED_NS { 100l };
constexpr fixed64_t  ENT_MAX_SPEED    { ENT_MAX_SPEED_NS };

} //NS