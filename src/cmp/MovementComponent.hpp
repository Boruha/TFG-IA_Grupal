#pragma once
#include <cmp/Component_t.hpp>
#include <utils/Vec2.hpp>

namespace AIP {

struct MovementComponent : Component_t {
  explicit MovementComponent(const entID entityID, const fixed32_t c_X, const fixed32_t c_Y) 
    : Component_t(entityID), coords(c_X, c_Y) { }

  fixed_vec2 coords { 0, 0 };
  fixed_vec2  dir   { 0, 0 };
};

}