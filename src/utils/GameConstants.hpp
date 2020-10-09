#pragma once
#include <chrono>
#include <ratio>
#include <cstdint>

//GameLoop
constexpr const double                                    FPS        { 60 };
constexpr const std::chrono::duration<double, std::milli> DELTATIME  { (1.0 / FPS) * 1000.0 };

//ManagerUpdateFunction
constexpr const float DeltaTime { 1.f / static_cast<float>(FPS) };

//Screen Settings
constexpr const uint32_t WINDOW_W { 1080 };
constexpr const uint32_t WINDOW_H { 720  };

constexpr const float  WINDOW_W_S { static_cast<float>(WINDOW_W) };
constexpr const float  WINDOW_H_S { static_cast<float>(WINDOW_H) };

