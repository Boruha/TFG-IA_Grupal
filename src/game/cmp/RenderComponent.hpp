#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/Color.hpp>
#include <game/utils/fvec2.hpp>

namespace AIP {

struct RenderComponent : BECS::Component_t {
    explicit RenderComponent(const BECS::entID entityID, const fint_t<uint64_t> s_W, const fint_t<uint64_t> s_H, const Color col) 
        : Component_t(entityID), sprite(s_W, s_H), sprite_C(col) { }

    fvec2<fint_t<uint64_t>> sprite { { 0ul }, { 0ul } };
    Color sprite_C { Color::Red };
};

}
