#pragma once
#include <cstdint>
#include <utils/ufixed64_t.hpp>

namespace AIP {

//ARRIVE B.
constexpr fixed64_t ENT_ARRIVE_DIST  { 20l };
constexpr fixed64_t ENT_ARRIVE_DIST2 { ENT_ARRIVE_DIST * ENT_ARRIVE_DIST };

constexpr fixed64_t ENT_SLOW_DIST  { 23l };
constexpr fixed64_t ENT_SLOW_DIST2 { ENT_SLOW_DIST * ENT_SLOW_DIST };

constexpr fixed64_t ENT_TIME_TO_TARGET { 0.1f };

//FLEE B.
constexpr fixed64_t ENT_FLEE_DIST  { 400l };
constexpr fixed64_t ENT_FLEE_DIST2 { ENT_FLEE_DIST * ENT_FLEE_DIST };

constexpr fixed64_t ENT_FAR_SLOW_DIST  { 395l };
constexpr fixed64_t ENT_FAR_SLOW_DIST2 { ENT_FAR_SLOW_DIST * ENT_FAR_SLOW_DIST };

//SEPARATION B.
constexpr fixed64_t ENT_SEPARATION_DIST  { 90l };
constexpr fixed64_t ENT_SEPARATION_DIST2 { ENT_SEPARATION_DIST * ENT_SEPARATION_DIST };
constexpr fixed64_t DECAY_COEFICIENT     { 1000l };

//COHESION B.
constexpr fixed64_t ENT_COHESION_DIST       { 150l };
constexpr fixed64_t ENT_COHESION_DIST2      { ENT_COHESION_DIST * ENT_COHESION_DIST };
//constexpr fixed64_t ENT_COHESION_LIMIT_DIST { 120l };

//MOVEMENT_SYS
constexpr fixed64_t ENT_MAX_SPEED  { 150l };
constexpr fixed64_t ENT_MAX_SPEED2 { ENT_MAX_SPEED * ENT_MAX_SPEED };

constexpr fixed64_t ENT_MAX_ACCEL  { 10l };
constexpr fixed64_t ENT_MAX_ACCEL2 { ENT_MAX_ACCEL };

} //NS