#pragma once

#include <utils/ufixed64_t.hpp>
#include <chrono>
#include <ratio>

namespace AIP {

//GameLoop
constexpr double FPS { 60.0 };

//ManagerUpdateFunction
constexpr float DeltaTime { 1.f / static_cast<float>(FPS) };

constexpr fixed64_t DELTATIME_MILLI { DeltaTime };
constexpr fixed64_t DELTATIME_MICRO { (DeltaTime * 1000000.f)/SCALE_S };

//Screen Settings
constexpr uint32_t WINDOW_W { 1920u };
constexpr uint32_t WINDOW_H { 1080u };

constexpr fixed64_t  WINDOW_W_S { static_cast<int64_t>(WINDOW_W) };
constexpr fixed64_t  WINDOW_H_S { static_cast<int64_t>(WINDOW_H) };

constexpr fixed64_t  HALF_WINDOW_W { static_cast<int64_t>(WINDOW_W/2) };
constexpr fixed64_t  HALF_WINDOW_H { static_cast<int64_t>(WINDOW_H/2) };

}