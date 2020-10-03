#pragma once
#include <cmp/Component_t.hpp>

#include <utils/Color.hpp>

namespace AIP {

struct RenderComponent : Component_t {
    explicit RenderComponent(const entID entityID, const uint32_t s_W, const uint32_t s_H, const Color col) 
        : Component_t(entityID), sprite_W(s_W), sprite_H(s_H), sprite_C(col) { }

    const uint32_t sprite_W { 0 };
    const uint32_t sprite_H { 0 };
    const Color    sprite_C { Color::Red };
};

}
