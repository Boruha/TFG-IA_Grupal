#pragma once
#include <game/utils/ufixed64_t.hpp>

namespace AIP {

//ARRIVE B.
constexpr fixed64_t ENT_ARRIVE_DIST  { 40l };
constexpr fixed64_t ENT_ARRIVE_DIST2 { ENT_ARRIVE_DIST * ENT_ARRIVE_DIST };

constexpr fixed64_t ENT_SLOW_DIST  { 43l };
constexpr fixed64_t ENT_SLOW_DIST2 { ENT_SLOW_DIST * ENT_SLOW_DIST };

constexpr fixed64_t ENT_TIME_TO_TARGET { 0.1f };

//FLEE B.
constexpr fixed64_t ENT_FLEE_DIST  { 600l };
constexpr fixed64_t ENT_FLEE_DIST2 { ENT_FLEE_DIST * ENT_FLEE_DIST };

constexpr fixed64_t ENT_FAR_SLOW_DIST  { 595l };
constexpr fixed64_t ENT_FAR_SLOW_DIST2 { ENT_FAR_SLOW_DIST * ENT_FAR_SLOW_DIST };

//SEPARATION B.
constexpr fixed64_t ENT_SEPARATION_DIST  { 180l };
constexpr fixed64_t ENT_SEPARATION_DIST2 { ENT_SEPARATION_DIST * ENT_SEPARATION_DIST };
constexpr fixed64_t DECAY_COEFICIENT     { 2400l };

//COHESION B.
constexpr fixed64_t ENT_COHESION_DIST       { 300l };
constexpr fixed64_t ENT_COHESION_DIST2      { ENT_COHESION_DIST * ENT_COHESION_DIST };

//MOVEMENT_SYS
constexpr fixed64_t ENT_MAX_SPEED  { 300l };
constexpr fixed64_t ENT_MAX_SPEED2 { ENT_MAX_SPEED * ENT_MAX_SPEED };

constexpr fixed64_t ENT_MAX_ACCEL  { 25l };
constexpr fixed64_t ENT_MAX_ACCEL2 { ENT_MAX_ACCEL };

} //NS