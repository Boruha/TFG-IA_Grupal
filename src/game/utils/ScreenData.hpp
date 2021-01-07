#pragma once
#include <game/utils/ufixed64_t.hpp>

namespace AIP {

//Screen Settings
constexpr uint32_t WINDOW_W { 1920u };
constexpr uint32_t WINDOW_H { 1080u };

constexpr fixed64_t  WINDOW_W_S { static_cast<int64_t>(WINDOW_W) };
constexpr fixed64_t  WINDOW_H_S { static_cast<int64_t>(WINDOW_H) };

constexpr fixed64_t  HALF_WINDOW_W { static_cast<int64_t>(WINDOW_W/2) };
constexpr fixed64_t  HALF_WINDOW_H { static_cast<int64_t>(WINDOW_H/2) };

}