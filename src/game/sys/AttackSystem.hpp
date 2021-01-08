#pragma once
#include <game/utils/EventHandler.hpp>

#include <memory>

namespace AIP {

template <typename Context_t>
struct AttackSystem : EventHandler {
    bool update(Context_t& context, const fixed64_t DeltaTime) noexcept;
};

} // NS