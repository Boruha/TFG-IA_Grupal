#include <sys/CollisionSystem.hpp>

#include <man/Manager_t.hpp>
#include <cmp/MovementComponent.hpp>
#include <cmp/RenderComponent.hpp>
#include <utils/GameConstants.hpp>
#include <ent/Entity_t.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

void
CollisionSystem::init() noexcept { }

bool
CollisionSystem::update(std::unique_ptr<Manager_t>& context) noexcept {
    auto& mov_cmp_vec = context->getMovementCmps();

    auto checkWinLimits = [&](std::unique_ptr<MovementComponent>& mov_cmp){
        auto& ent       = context->getEntityByID(mov_cmp->getEntityID());
        auto* ren_cmp   = ent->getComponent<RenderComponent>();

        auto& c_X = mov_cmp->coord_X; 
        auto& c_Y = mov_cmp->coord_Y;
        auto  s_W = static_cast<int32_t>(ren_cmp->sprite_W);
        auto  s_H = static_cast<int32_t>(ren_cmp->sprite_H);
        
        if(c_X + s_W  > WINDOW_W_S ) { c_X = s_W;              } //Eje X
        if(c_X - s_W  < 0          ) { c_X = WINDOW_W_S - s_W; }

        if(c_Y + s_H  > WINDOW_H_S ) { c_Y = s_H;              } //Eje Y
        if(c_Y - s_H  < 0          ) { c_Y = WINDOW_H_S - s_H; }

    };

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), checkWinLimits);

    return true;
}

} //NS