#pragma once
#include <game/utils/fint_t.hpp>
#include <game/utils/EventHandler.hpp>
#include <game/utils/GameConditions.hpp>

namespace AIP {

template <typename Context_t>
struct DeathSystem : EventHandler {
    GameConditions update(Context_t& context) noexcept;
};

} // NS