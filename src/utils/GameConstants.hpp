#pragma once
#include <chrono>
#include <ratio>
#include <cstdint>

//GameLoop
constexpr const double                                    FPS        { 60 };
constexpr const std::chrono::duration<double, std::milli> DELTATIME  { (1.0 / FPS) * 1000.0 };

//Screen Settings
constexpr const uint32_t WINDOW_W { 1080 };
constexpr const uint32_t WINDOW_H { 720  };

constexpr const int32_t  WINDOW_W_S { static_cast<int32_t>(WINDOW_W) };
constexpr const int32_t  WINDOW_H_S { static_cast<int32_t>(WINDOW_H) };

