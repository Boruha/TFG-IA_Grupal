#pragma once
#include <cmp/Component_t.hpp>

#include <utils/Color.hpp>
#include <utils/Vec2.hpp>

namespace AIP {

struct RenderComponent : Component_t {
    explicit RenderComponent(const entID entityID, const uint32_t s_W, const uint32_t s_H, const Color col) 
        : Component_t(entityID), sprite(s_W, s_H), sprite_C(col) { }

    const Vec2<uint32_t> sprite   { 0, 0 };
    const Color          sprite_C { Color::Red };
};

}
