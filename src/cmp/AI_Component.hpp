#pragma once
#include <cmp/Component_t.hpp>
#include <array>

namespace AIP {

struct AI_Component : Component_t {
    explicit AI_Component(entID eid) : Component_t(eid) { }
};

} //NS