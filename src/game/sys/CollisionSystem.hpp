#pragma once
#include <game/utils/fvec2.hpp>

#include <memory>

namespace AIP {

template <typename Context_t>
struct CollisionSystem {
    void update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;
};

} // NS
