#pragma once
#include <cmp/Component_t.hpp>
#include <array>

namespace AIP {

struct AI_Component : Component_t {
    explicit AI_Component(entID eid) : Component_t(eid) {}

    std::array<float,8> patrol_coord { 10.f,10.f, 100.f,50.f, 100.f,300.f, 100.f,600.f };
    std::size_t         patrol_index { 0 };

};

} //NS