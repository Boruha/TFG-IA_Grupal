#pragma once
#include <game/utils/fvec2.hpp>

namespace AIP {

template <typename Context_t>
struct InputSystem {
    bool update(Context_t& context) noexcept;
};


}