#pragma once
#include <ecs/cmp/Component_t.hpp>
#include <game/utils/fvec2.hpp>

namespace AIP {

struct Collider2DCmp : BECS::Component_t {
    explicit Collider2DCmp(const BECS::entID entityID, const uint32_t s_W, const uint32_t s_H) : Component_t(entityID), 
        p2(   static_cast<int64_t>(s_W), static_cast<int64_t>(s_H) ),
        size( static_cast<int64_t>((s_W+s_H)/2u) ) 
        { }

    fvec2<fint_t<int64_t>> p2   { { 0l }, { 0l } }; //mov.coords + p2 = down-right corner
    fint_t<int64_t>        size { 0l };
};

}