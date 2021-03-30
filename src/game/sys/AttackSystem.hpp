#pragma once
#include <game/utils/fvec2.hpp>

namespace AIP {

template <typename Context_t>
struct AttackSystem {
    void update(Context_t& context) noexcept;
};

} // NS