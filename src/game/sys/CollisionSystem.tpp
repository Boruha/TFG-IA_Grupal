#include <game/sys/CollisionSystem.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/RenderComponent.hpp>
#include <game/cmp/Collider2DCmp.hpp>
#include <game/cmp/EventCmp_t.hpp>
#include <game/utils/ScreenData.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

template <typename Context_t>
void
CollisionSystem<Context_t>::update(Context_t& context) noexcept {
    auto& mov_vec = context.template getComponentVector<MovementComponent>();

    bulletsCollision(context, context.getEnemyIDs(), context.getAllyBullets() );
    bulletsCollision(context, context.getAllyIDs() , context.getEnemBullets() );

    std::for_each(begin(mov_vec), end(mov_vec),
        [&](MovementComponent& mov) {
            auto& collider2D = context.template getCmpByEntityID<Collider2DCmp>( mov.getEntityID() );
            auto& coord      = mov.coords;

            const auto p2 { coord + collider2D.p2 };
            const auto sz { collider2D.size };

            //eje X
            if( p2.x > F_H_WINDOW_W )
                    coord.x = F_H_WINDOW_W_N + sz;
            
            if( coord.x < F_H_WINDOW_W_N )
                    coord.x = F_H_WINDOW_W - sz;
            
            //eje Y
            if( p2.y > F_H_WINDOW_H )
                    coord.y = F_H_WINDOW_H_N + sz;
            
            if( coord.y < F_H_WINDOW_H_N )
                    coord.y = F_H_WINDOW_H - sz;
    });

}

template <typename Context_t>
void                        
CollisionSystem<Context_t>::bulletsCollision(Context_t& context, std::vector<BECS::entID>& team, std::vector<BECS::entID>& bullets) noexcept {
    auto axis_x { false };
    auto axis_y { false };

    for(auto& ent : team) {
        auto& entMov    = context.template getCmpByEntityID<MovementComponent>(ent);
        auto& entColl2D = context.template getCmpByEntityID<Collider2DCmp>(ent);
        auto& entCoords = entMov.coords;

        const auto entP2 { entCoords + entColl2D.p2 };

        for(auto& bullet : bullets) {
            auto& bulMov    = context.template getCmpByEntityID<MovementComponent>(bullet);
            auto& bulColl2D = context.template getCmpByEntityID<Collider2DCmp>(bullet);
            auto& bulCoords = bulMov.coords;

            const auto bulP2 { bulCoords + bulColl2D.p2 };
            
            //eje x
            if(entCoords.x < bulP2.x && entCoords.x > bulCoords.x)
                axis_x = true;
            if(entP2.x < bulP2.x && entP2.x > bulCoords.x)
                axis_x = true;

            //eje y
            if(entCoords.y < bulP2.y && entCoords.y > bulCoords.y)
                axis_y = true;
            if(entP2.y < bulP2.y && entP2.y > bulCoords.y)
                axis_y = true;

            if(axis_x && axis_y) {
                auto& eventCmp = context.template getSCmpByType<EventCmp_t>();
                eventCmp.death_msg.emplace(bullet, EntType::Bullet);
                eventCmp.attack_msg.emplace_back(bullet, ent, 4);
            }
            
            axis_y = axis_x = false;
        }
    }
}

} //NS