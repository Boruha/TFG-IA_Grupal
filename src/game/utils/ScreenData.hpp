#pragma once
#include <game/utils/fint_t.hpp>

namespace AIP {

/*  World  = cont.  = fint_t; -> MovementComponent.pos
    Camera = cont.  = fint_t; -> CamSystem = MovementComponent.pos - Cam.MovementComponent.pos
    Screen = pixels = uint_t; -> contToScreen( CamSystem )
*/

//Screen Settings to setup window render->engine. Range -> X:[0 - Win_W] / Y:[0 - Win_H]
constexpr uint32_t UWIN_W { 1920u };
constexpr uint32_t UWIN_H { 1080u };

constexpr int64_t WIN_W { static_cast<int64_t>(UWIN_W) };
constexpr int64_t WIN_H { static_cast<int64_t>(UWIN_H) };

constexpr int64_t HALF_WIN_W { WIN_W/2 };
constexpr int64_t HALF_WIN_H { WIN_H/2 };

//World coords to setup level limits. Range -> X:[0 - World_W] / Y:[0 - World_H]
constexpr int64_t WORLD_W { WIN_W + HALF_WIN_W };
constexpr int64_t WORLD_H { WIN_H + HALF_WIN_H };

constexpr int64_t HALF_WORLD_W { WORLD_W/2 };
constexpr int64_t HALF_WORLD_H { WORLD_H/2 };

constexpr fint_t FIXED_HALF_WORLD_W { HALF_WORLD_W };
constexpr fint_t FIXED_HALF_WORLD_H { HALF_WORLD_H };

constexpr fint_t FIXED_HALF_WORLD_W_N { HALF_WORLD_W * -1 };
constexpr fint_t FIXED_HALF_WORLD_H_N { HALF_WORLD_H * -1 };

}