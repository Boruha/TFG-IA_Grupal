#pragma once
#include <game/utils/fint_t.hpp>

namespace AIP {

//Screen Settings
constexpr uint32_t U_WINDOW_W { 1920u };
constexpr uint32_t U_WINDOW_H { 1080u };

constexpr int64_t WINDOW_W { static_cast<int64_t>(U_WINDOW_W) };
constexpr int64_t WINDOW_H { static_cast<int64_t>(U_WINDOW_H) };

constexpr int64_t H_WINDOW_W { WINDOW_W/2 };
constexpr int64_t H_WINDOW_H { WINDOW_H/2 };

constexpr fint_t H_WINDOW_W_N { H_WINDOW_W * -1 };
constexpr fint_t H_WINDOW_H_N { H_WINDOW_H * -1 };

/*fint_t*/

constexpr fint_t F_WINDOW_W { WINDOW_W };
constexpr fint_t F_WINDOW_H { WINDOW_H };

constexpr fint_t F_H_WINDOW_W { H_WINDOW_W };
constexpr fint_t F_H_WINDOW_H { H_WINDOW_H };

constexpr fint_t F_H_WINDOW_W_N { H_WINDOW_W * -1 };
constexpr fint_t F_H_WINDOW_H_N { H_WINDOW_H * -1 };

}