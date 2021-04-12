#include <game/sys/CollisionSystem.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/Collider2DCmp.hpp>
#include <game/cmp/EventCmp_t.hpp>
#include <game/cmp/BulletCmp.hpp>
#include <game/utils/ScreenData.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {


template <typename Context_t>
void
CollisionSystem<Context_t>::update(Context_t& context) noexcept {
    auto& movCmps = context.template getComponentVector<MovementComponent>();

    bulletsCollision(context, context.getEnemyIDs(), context.getAllyBullets() );
    bulletsCollision(context, context.getAllyIDs() , context.getEnemBullets() );
    
    checkWorldLimits(context, movCmps);
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
                auto& eventCmp   = context.template getSCmpByType<EventCmp_t>();
                auto& bulletInfo = context.template getCmpByEntityID<BulletCmp>(bullet);

                eventCmp.death_msg.emplace(bullet, EntType::Bullet);
                eventCmp.attack_msg.emplace_back(bulletInfo.shooter, ent, bulletInfo.damage);
            }
            
            axis_y = axis_x = false;
        }
    }
}

template <typename Context_t>
void                        
CollisionSystem<Context_t>::checkWorldLimits(Context_t& context, std::vector<MovementComponent>& movCmps) noexcept {
    std::for_each(begin(movCmps), end(movCmps),
        [&](MovementComponent& mov) {
            const auto& collider2D = context.template getCmpByEntityID<Collider2DCmp>( mov.getEntityID() );
                  auto& coord      = mov.coords;
            const auto& p2         { collider2D.p2 };
            const auto  locatedP2  { coord + p2 };

            //eje X
            if( locatedP2.x > FIXED_HALF_WORLD_W )
                    coord.x = FIXED_HALF_WORLD_W - p2.x;
            
            if( coord.x < FIXED_HALF_WORLD_W_N )
                    coord.x = FIXED_HALF_WORLD_W_N;
            
            //eje Y
            if( locatedP2.y > FIXED_HALF_WORLD_H )
                    coord.y = FIXED_HALF_WORLD_H - p2.y;

            if( coord.y < FIXED_HALF_WORLD_H_N )
                    coord.y = FIXED_HALF_WORLD_H_N;
    });
}


} //NS