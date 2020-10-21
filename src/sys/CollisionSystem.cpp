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
CollisionSystem::update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept {
    auto& mov_cmp_vec = context->getMovementCmps();

    auto checkWinLimits = [&](std::unique_ptr<MovementComponent>& mov_cmp){
        auto& ent       = context->getEntityByID(mov_cmp->getEntityID());
        auto* ren_cmp   = ent->getComponent<RenderComponent>();

              auto& coord  = mov_cmp->coords;
        const auto& direct = mov_cmp->dir;
        const auto& size_W = ren_cmp->sprite.x;
        const auto& size_H = ren_cmp->sprite.y;
        
        //eje X
        if(direct.x > 0) {
            if(coord.x > WINDOW_W_S - size_W)
                coord.x = size_W;
        } else {
            if(coord.x < size_W)
                coord.x = WINDOW_W_S - size_W;
        }
        
        //eje Y
        if(direct.y > 0) {
            if(coord.y > WINDOW_H_S - size_H)
                coord.y = size_H;
        } else {
            if(coord.y < size_H)
                coord.y = WINDOW_H_S - size_H;
        }
    };

    /* NOT WELL TESTED */

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), checkWinLimits);

    return true;
}

} //NS