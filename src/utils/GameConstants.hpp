#pragma once

#include <chrono>
#include <ratio>
#include <utils/ufixed32_t.hpp>

namespace AIP {

//GameLoop
constexpr double FPS { 60.0 };
//constexpr std::chrono::duration<double, std::milli> DELTATIME        { (1.0 / FPS) * 1000.0 };
//constexpr std::chrono::duration<double, std::micro> DELTATIME_MICRO  { (1.0 / FPS) * 1000000.0 };

//ManagerUpdateFunction
constexpr float DeltaTime { 1.f / static_cast<float>(FPS) };

constexpr fixed32_t DELTATIME_MILLI { DeltaTime };
constexpr fixed32_t DELTATIME_MICRO { 65 };

//Screen Settings
constexpr uint32_t WINDOW_W { 1080u };
constexpr uint32_t WINDOW_H { 720u  };

constexpr fixed32_t  WINDOW_W_S { static_cast<int32_t>(WINDOW_W) };
constexpr fixed32_t  WINDOW_H_S { static_cast<int32_t>(WINDOW_H) };

constexpr fixed32_t  HALF_WINDOW_W { static_cast<int32_t>(WINDOW_W/2) };
constexpr fixed32_t  HALF_WINDOW_H { static_cast<int32_t>(WINDOW_H/2) };

}