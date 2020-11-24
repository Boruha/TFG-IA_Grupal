#pragma once
#include <cstdint>
#include <utils/ufixed64_t.hpp>

namespace AIP {

//ARRIVE B.
constexpr fixed64_t ENT_ARRIVE_DIST  { 10l };
constexpr fixed64_t ENT_ARRIVE_DIST2 { ENT_ARRIVE_DIST * ENT_ARRIVE_DIST };

constexpr fixed64_t ENT_SLOW_DIST  { 25l };
constexpr fixed64_t ENT_SLOW_DIST2 { ENT_SLOW_DIST * ENT_SLOW_DIST };

constexpr fixed64_t ENT_TIME_TO_TARGET { 0.1f };


//MOVEMENT_SYS
constexpr int64_t    ENT_MAX_SPEED_NS { 150l };
constexpr fixed64_t  ENT_MAX_SPEED    { ENT_MAX_SPEED_NS };

constexpr fixed64_t  ENT_MAX_ACCEL  { 7l };
constexpr fixed64_t  ENT_MAX_ACCEL2 { ENT_MAX_ACCEL };


} //NS