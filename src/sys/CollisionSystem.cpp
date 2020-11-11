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
        const auto size_W  = static_cast<int32_t>(ren_cmp->sprite.x.number);
        const auto size_H  = static_cast<int32_t>(ren_cmp->sprite.y.number);
        
        //eje X
        if(coord.x.number + size_W > WINDOW_W_S.number/2)
                coord.x.number = (-WINDOW_W_S.number/2) + size_W;
        
        if(coord.x.number - size_W < -WINDOW_W_S.number/2)
                coord.x.number = (WINDOW_W_S.number/2) - size_W;

        //eje Y
        if(coord.y.number + size_H > WINDOW_H_S.number/2)
                coord.y.number = (-WINDOW_H_S.number/2) + size_H;
        
        if(coord.y.number - size_H < -WINDOW_H_S.number/2)
                coord.y.number = (WINDOW_H_S.number/2) - size_H;

        
        //eje Y
        //if(direct.y.number > 0) {
        //    if(coord.y.number > WINDOW_H_S.number - size_H)
        //        coord.y.number = size_H;
        //} else {
        //    if(coord.y.number < size_H)
        //        coord.y.number = WINDOW_H_S.number - size_H;
        //}
    };

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), checkWinLimits);

    return true;
}

} //NS