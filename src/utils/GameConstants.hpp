#pragma once
#include <chrono>
#include <ratio>
#include <utils/ufixed32_t.hpp>

namespace AIP {

//GameLoop
constexpr const double                                    FPS        { 60 };
constexpr const std::chrono::duration<double, std::milli> DELTATIME  { (1.0 / FPS) * 1000.0 };

//ManagerUpdateFunction
constexpr const float DeltaTime { 1.f / static_cast<float>(FPS) };

//Screen Settings
constexpr const uint32_t WINDOW_W { 1080u };
constexpr const uint32_t WINDOW_H { 720u  };

constexpr const ufixed32_t  WINDOW_W_S { WINDOW_W };
constexpr const ufixed32_t  WINDOW_H_S { WINDOW_H };

}