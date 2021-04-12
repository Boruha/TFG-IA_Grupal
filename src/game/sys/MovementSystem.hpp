#pragma once
#include <game/cmp/MovementComponent.hpp>

#include <memory>

namespace AIP {

template <typename Context_t>
struct MovementSystem{
    void update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;

private:
    void moveEntity(MovementComponent& mov, const fint_t<int64_t> DeltaTime) noexcept;
    void moveCamera(Context_t& context) noexcept;
};

} //NS
