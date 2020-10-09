#include <sys/CollisionSystem.hpp>

#include <man/Manager_t.hpp>
#include <cmp/MovementComponent.hpp>
#include <cmp/RenderComponent.hpp>
#include <utils/GameConstants.hpp>
#include <ent/Entity_t.hpp>

#include <algorithm>

namespace AIP {

void
CollisionSystem::init() noexcept { }

bool
CollisionSystem::update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept {
    auto& mov_cmp_vec = context->getMovementCmps();

    auto checkWinLimits = [&](std::unique_ptr<MovementComponent>& mov_cmp){
        auto& ent       = context->getEntityByID(mov_cmp->getEntityID());
        auto* ren_cmp   = ent->getComponent<RenderComponent>();

        auto& coord = mov_cmp->coords;
        auto  s_W = static_cast<float>(ren_cmp->sprite.x);
        auto  s_H = static_cast<float>(ren_cmp->sprite.y);
        
        if(coord.x + s_W  > WINDOW_W_S ) { coord.x = s_W;              } //Eje X
        if(coord.x - s_W  < 0          ) { coord.x = WINDOW_W_S - s_W; }

        if(coord.y + s_H  > WINDOW_H_S ) { coord.y = s_H;              } //Eje Y
        if(coord.y - s_H  < 0          ) { coord.y = WINDOW_H_S - s_H; }

    };

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), checkWinLimits);

    return true;
}

} //NS