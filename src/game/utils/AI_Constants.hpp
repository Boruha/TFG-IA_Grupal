#pragma once
#include <game/utils/fint_t.hpp>

namespace AIP {

//SENSOR
constexpr fint_t<int64_t> VISION_DIST  { 150l };
constexpr fint_t<int64_t> VISION_DIST2 { VISION_DIST * VISION_DIST };

constexpr fint_t<int64_t> MEELE_ATK_DIST  { 50l };
constexpr fint_t<int64_t> MEELE_ATK_DIST2 { MEELE_ATK_DIST * MEELE_ATK_DIST };

constexpr fint_t<int64_t> RANGE_ATK_DIST  { 120l };
constexpr fint_t<int64_t> RANGE_ATK_DIST2 { RANGE_ATK_DIST * RANGE_ATK_DIST };

//ARRIVE B.
constexpr fint_t<int64_t> ENT_ARRIVE_DIST  { 50l };
constexpr fint_t<int64_t> ENT_ARRIVE_DIST2 { ENT_ARRIVE_DIST * ENT_ARRIVE_DIST };

constexpr fint_t<int64_t> ENT_SLOW_DIST  { 55l };
constexpr fint_t<int64_t> ENT_SLOW_DIST2 { ENT_SLOW_DIST * ENT_SLOW_DIST };

constexpr fint_t<int64_t> ENT_TIME_TO_TARGET { 0.2f };

//FLEE B.
constexpr fint_t<int64_t> ENT_FLEE_DIST  { 600l };
constexpr fint_t<int64_t> ENT_FLEE_DIST2 { ENT_FLEE_DIST * ENT_FLEE_DIST };

constexpr fint_t<int64_t> ENT_FAR_SLOW_DIST  { 595l };
constexpr fint_t<int64_t> ENT_FAR_SLOW_DIST2 { ENT_FAR_SLOW_DIST * ENT_FAR_SLOW_DIST };

//SEPARATION B.
constexpr fint_t<int64_t> ENT_SEPARATION_DIST  { 200l };
constexpr fint_t<int64_t> ENT_SEPARATION_DIST2 { ENT_SEPARATION_DIST * ENT_SEPARATION_DIST };
constexpr fint_t<int64_t> DECAY_COEFICIENT_SEP { 10000l };

//COHESION B.
constexpr fint_t<int64_t> ENT_COHESION_DIST    { 150l };
constexpr fint_t<int64_t> ENT_COHESION_DIST2   { ENT_COHESION_DIST * ENT_COHESION_DIST };
constexpr fint_t<int64_t> DECAY_COEFICIENT_COH { 3000l };

//MOVEMENT_SYS
constexpr fint_t<int64_t> ENT_MAX_SPEED  { 280l };
constexpr fint_t<int64_t> ENT_MAX_SPEED2 { ENT_MAX_SPEED * ENT_MAX_SPEED };

constexpr fint_t<int64_t> ENT_MAX_ACCEL  { 15l };
constexpr fint_t<int64_t> ENT_MAX_ACCEL2 { ENT_MAX_ACCEL };

} //NS