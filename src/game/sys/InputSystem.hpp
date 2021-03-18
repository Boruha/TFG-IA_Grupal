#pragma once
#include <game/utils/EventHandler.hpp>
#include <game/utils/fvec2.hpp>

namespace AIP {

template <typename Context_t>
struct InputSystem : EventHandler {
    bool     update(Context_t& context) noexcept;
};


}