#pragma once
#include <chrono>
#include <ratio>
#include <cstdint>

//GameLoop
constexpr const double                                    FPS        { 60 };
constexpr const std::chrono::duration<double, std::milli> DELTATIME  { (1.0 / FPS) * 1000.0 };

//Screen Settings
constexpr const uint32_t WINDOW_W { 640 };
constexpr const uint32_t WINDOW_H { 360 };
