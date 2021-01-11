#pragma once
#include <game/utils/fint_t.hpp>

namespace AIP {

//Screen Settings
constexpr uint32_t WINDOW_W { 1920ul };
constexpr uint32_t WINDOW_H { 1080ul };

constexpr fint_t<int64_t> WINDOW_W_S { static_cast<int64_t>(WINDOW_W) };
constexpr fint_t<int64_t> WINDOW_H_S { static_cast<int64_t>(WINDOW_H) };

constexpr fint_t<int64_t> HALF_WINDOW_W { static_cast<int64_t>(WINDOW_W/2) };
constexpr fint_t<int64_t> HALF_WINDOW_H { static_cast<int64_t>(WINDOW_H/2) };

}