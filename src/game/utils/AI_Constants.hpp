#pragma once
#include <game/utils/fint_t.hpp>

namespace AIP {

//SENSOR
constexpr fint_t<int64_t> VISION_DIST  { 150l };
constexpr fint_t<int64_t> VISION_DIST2 { VISION_DIST * VISION_DIST };

constexpr fint_t<int64_t> ATTACK_DIST  { 45l };
constexpr fint_t<int64_t> ATTACK_DIST2 { ATTACK_DIST * ATTACK_DIST };

//ARRIVE B.
constexpr fint_t<int64_t> ENT_ARRIVE_DIST  { 40l };
constexpr fint_t<int64_t> ENT_ARRIVE_DIST2 { ENT_ARRIVE_DIST * ENT_ARRIVE_DIST };

constexpr fint_t<int64_t> ENT_SLOW_DIST  { 43l };
constexpr fint_t<int64_t> ENT_SLOW_DIST2 { ENT_SLOW_DIST * ENT_SLOW_DIST };

constexpr fint_t<int64_t> ENT_TIME_TO_TARGET { 0.1f };

//FLEE B.
constexpr fint_t<int64_t> ENT_FLEE_DIST  { 600l };
constexpr fint_t<int64_t> ENT_FLEE_DIST2 { ENT_FLEE_DIST * ENT_FLEE_DIST };

constexpr fint_t<int64_t> ENT_FAR_SLOW_DIST  { 595l };
constexpr fint_t<int64_t> ENT_FAR_SLOW_DIST2 { ENT_FAR_SLOW_DIST * ENT_FAR_SLOW_DIST };

//SEPARATION B.
constexpr fint_t<int64_t> ENT_SEPARATION_DIST  { 180l };
constexpr fint_t<int64_t> ENT_SEPARATION_DIST2 { ENT_SEPARATION_DIST * ENT_SEPARATION_DIST };
constexpr fint_t<int64_t> DECAY_COEFICIENT     { 3500l };

//COHESION B.
constexpr fint_t<int64_t> ENT_COHESION_DIST  { 220l };
constexpr fint_t<int64_t> ENT_COHESION_DIST2 { ENT_COHESION_DIST * ENT_COHESION_DIST };

//MOVEMENT_SYS
constexpr fint_t<int64_t> ENT_MAX_SPEED  { 300l };
constexpr fint_t<int64_t> ENT_MAX_SPEED2 { ENT_MAX_SPEED * ENT_MAX_SPEED };

constexpr fint_t<int64_t> ENT_MAX_ACCEL  { 25l };
constexpr fint_t<int64_t> ENT_MAX_ACCEL2 { ENT_MAX_ACCEL };

} //NS