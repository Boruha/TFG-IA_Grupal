#pragma once
#include <game/cmp/MovementComponent.hpp>

#include <memory>

namespace AIP {

template <typename Context_t>
struct MovementSystem{
    void update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;
};

} //NS
