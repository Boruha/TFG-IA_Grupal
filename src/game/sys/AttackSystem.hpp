#pragma once
#include <game/utils/EventHandler.hpp>
#include <game/utils/fvec2.hpp>

#include <memory>

namespace AIP {

template <typename Context_t>
struct AttackSystem : EventHandler {
    bool update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;
};

} // NS