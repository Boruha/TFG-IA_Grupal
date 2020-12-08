#pragma once
#include <utils/ufixed64_t.hpp>

namespace AIP {

//FrameRate
constexpr float FPS         { 60.f };
constexpr float DeltaTime   { 1.f / FPS };
constexpr float Micro_multi { 1000000.f };

constexpr fixed64_t LOOP_TIME { (DeltaTime * Micro_multi)/SCALE_S };

//DeltaTime
constexpr fixed64_t DELTA_TIME  { DeltaTime };

}