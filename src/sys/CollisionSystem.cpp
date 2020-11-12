#include <sys/CollisionSystem.hpp>

#include <man/Manager_t.hpp>

#include <cmp/MovementComponent.hpp>
#include <cmp/RenderComponent.hpp>

#include <utils/GameConstants.hpp>
#include <utils/AI_Constants.hpp>

#include <ent/Entity_t.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

void
CollisionSystem::init() noexcept { }

bool
CollisionSystem::update(const std::unique_ptr<Manager_t>& context, const fixed32_t DeltaTime) noexcept {
    auto& mov_cmp_vec = context->getMovementCmps();

    auto checkWinLimits = [&](std::unique_ptr<MovementComponent>& mov_cmp) {
        auto& ent       = context->getEntityByID(mov_cmp->getEntityID());
        auto* ren_cmp   = ent->getComponent<RenderComponent>();

              auto& coord  = mov_cmp->coords;
        const auto size_W  = static_cast<fixed32_t>(ren_cmp->sprite.x);
        const auto size_H  = static_cast<fixed32_t>(ren_cmp->sprite.y);
        
        //eje X
        if( coord.x + size_W > HALF_WINDOW_W )
                coord.x = (HALF_WINDOW_W * -1) + size_W;
        
        if( coord.x - size_W < (HALF_WINDOW_W * -1) )
                coord.x = HALF_WINDOW_W - size_W;

        //eje Y
        if( coord.y + size_H > HALF_WINDOW_H )
                coord.y = (HALF_WINDOW_H * -1) + size_H;
        
        if( coord.y - size_H < (HALF_WINDOW_H * -1) )
                coord.y = HALF_WINDOW_H - size_H;
    };

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), checkWinLimits);

    return true;
}

} //NS