/*
Copyright (C) <2020-2021> Borja Pozo Wals (Tw: @Chico_Riot | GitHub: Boruha)

This file is part of 'TFG: Gestión y manejo de comportamientos grupales 
de entidades en videojuegos'.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <game/sys/CollisionSystem.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/Collider2DCmp.hpp>
#include <game/cmp/EventCmp_t.hpp>
#include <game/cmp/TriggerCmp_t.hpp>
#include <game/cmp/BulletCmp.hpp>
#include <game/cmp/RenderComponent.hpp>
#include <game/utils/ScreenData.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {


template <typename Context_t>
GameConditions
CollisionSystem<Context_t>::update(Context_t& context) noexcept {
    auto result   { GameConditions::Loop };
    auto& movCmps = context.template getComponentVector<MovementComponent>();

    bulletsCollision(context, context.getEnemyIDs(), context.getAllyBullets() );
    bulletsCollision(context, context.getAllyIDs() , context.getEnemBullets() );
    
    checkWorldLimits(context, movCmps);

    result = checkTriggerBoxes(context);

    return result;
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
            if(bulCoords.x < entP2.x && entCoords.x < bulCoords.x)
                axis_x = true;
            if(bulP2.x < entP2.x && entCoords.x < bulP2.x)
                axis_x = true;

            //eje y
            if(bulCoords.y < entP2.y && entCoords.y < bulCoords.y)
                axis_y = true;
            if(bulP2.y < entP2.y && entCoords.y < bulP2.y)
                axis_y = true;

            if(axis_x && axis_y) {
                auto& eventCmp   = context.template getSCmpByType<EventCmp_t>();
                auto& bulletInfo = context.template getCmpByEntityID<BulletCmp>(bullet);
                auto& bulletRend = context.template getCmpByEntityID<RenderComponent>(bullet);                

                bulletRend.sprite_C = Color::Green;

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

template <typename Context_t>
GameConditions 
CollisionSystem<Context_t>::checkTriggerBoxes(Context_t& context) noexcept {
    auto  result      { GameConditions::Loop };
    auto  axis_x      { false };
    auto  axis_y      { false };

    auto  player   = context.getPlayerID();
    auto& pjMov    = context.template getCmpByEntityID<MovementComponent>(player);
    auto& pjColl2D = context.template getCmpByEntityID<Collider2DCmp>(player);
    auto& pjCoords = pjMov.coords;
    auto  pjP2     { pjCoords + pjColl2D.p2 };

    auto& triggerCmps = context.template getComponentVector<TriggerCmp_t>();

    for(auto& trigger : triggerCmps) {
        auto& entMov    = context.template getCmpByEntityID<MovementComponent>(trigger.getEntityID());
        auto& entColl2D = context.template getCmpByEntityID<Collider2DCmp>(trigger.getEntityID());
        auto& entCoords = entMov.coords;
        auto  entP2     { entCoords + entColl2D.p2 };
        
        //eje x
        if(pjCoords.x < entP2.x && entCoords.x < pjCoords.x)
            axis_x = true;
        if(pjP2.x < entP2.x && entCoords.x < pjP2.x)
            axis_x = true;

        //eje y
        if(pjCoords.y < entP2.y && entCoords.y < pjCoords.y)
            axis_y = true;
        if(pjP2.y < entP2.y && entCoords.y < pjP2.y)
            axis_y = true;

        if(axis_x && axis_y) {
            result = trigger.event;
            break;
        }
        
        axis_y = axis_x = false;
    }

    return result;
} 


} //NS