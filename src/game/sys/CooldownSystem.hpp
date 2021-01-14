#pragma once
#include <game/utils/fint_t.hpp>

namespace AIP {

template <typename Context_t>
struct CooldownSystem {
    void update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;
};

} // NS