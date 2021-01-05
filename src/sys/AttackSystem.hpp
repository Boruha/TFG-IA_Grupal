#pragma once
#include <sys/System_t.hpp>

#include <memory>

namespace AIP {

template <typename Context_t>
struct AttackSystem : System_t {
    bool update(Context_t& context, const fixed64_t DeltaTime) noexcept;
};

} // NS