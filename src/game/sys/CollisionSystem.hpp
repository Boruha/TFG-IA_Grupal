#pragma once
#include <memory>

namespace AIP {

template <typename Context_t>
struct CollisionSystem {
    bool update(Context_t& context, const fixed64_t DeltaTime) noexcept;
};

} // NS
