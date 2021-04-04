#pragma once
#include <game/utils/fint_t.hpp>
#include <game/utils/GameConditions.hpp>

namespace AIP {

struct AI_Component;
struct EventCmp_t;

template <typename Context_t>
struct DeathSystem {
    GameConditions update(Context_t& context) noexcept;
};

} // NS