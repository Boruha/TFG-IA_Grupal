#pragma once
#include <ecs/cmp/Component_t.hpp>
#include <game/utils/fvec2.hpp>

namespace AIP {

struct Collider2DCmp : BECS::Component_t {
    explicit Collider2DCmp(const BECS::entID entityID, const uint32_t s_W, const uint32_t s_H) : Component_t(entityID), 
        p1( -1 * static_cast<int64_t>(s_W/2u), -1 * static_cast<int64_t>(s_H/2u) ),
        p2(      static_cast<int64_t>(s_W/2u),      static_cast<int64_t>(s_H/2u) ),
        size(    static_cast<int64_t>((s_W+s_H)/2u) ) { }

    fvec2<fint_t<int64_t>> p1   { { 0l }, { 0l } }; //up-left corner
    fvec2<fint_t<int64_t>> p2   { { 0l }, { 0l } }; //down-right corner
    fint_t<int64_t>        size { 0l };
};

}