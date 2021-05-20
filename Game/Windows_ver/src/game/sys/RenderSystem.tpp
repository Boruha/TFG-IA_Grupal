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

#include <game/sys/RenderSystem.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/Collider2DCmp.hpp>
#include <game/cmp/InterfaceControl.hpp>
#include <game/cmp/TextCmp_t.hpp>
#include <game/utils/ScreenData.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {
template <typename Context_t>    
RenderSystem<Context_t>::RenderSystem(const int64_t w, const int64_t h)
    : engine( std::make_unique<eGL::EngineManager>(w, h, "Prototype_IA") ) {
      engine->setMiniMapFraction(WORLD_W, WORLD_H);
}

//LOOP
template <typename Context_t>
bool
RenderSystem<Context_t>::update(Context_t& context) noexcept {    
    const auto& renderCmps = context.template getComponentVector<RenderComponent>();
    const auto& textCmps   = context.template getComponentVector<TextCmp_t>();
    
    /* camera info */
    const auto& cameraID  = context.getCameraID();
    const auto& camMov    = context.template getCmpByEntityID<MovementComponent>(cameraID);
    const auto& camColl2D = context.template getCmpByEntityID<Collider2DCmp>(cameraID);
    const auto& camCoords       { camMov.coords };
    const auto& camP2           { camColl2D.p2 };
    const auto  camLocatedP2    { camCoords + camP2 };
          auto  camScreenCoords { continuousToScreen(camCoords) }; //WORLD COORDS


    engine->start_frame();
    engine->minimap();

    drawInterface(context);

    std::for_each(cbegin(renderCmps), cend(renderCmps), 
        [&](const RenderComponent& render) {
                  auto& mov        = context.template getCmpByEntityID<MovementComponent>( render.getEntityID() );        
            const auto& collider2D = context.template getCmpByEntityID<Collider2DCmp>( render.getEntityID() );
            const auto& coords     { mov.coords };
            const auto& p2         { collider2D.p2 };
            const auto  locatedP2  { coords + p2 };

            auto screen_coords { continuousToScreen(coords) }; //WORLD COORDS
            auto& sprite       = render.sprite;

            engine->drawInMinimap( screen_coords.x, screen_coords.y, sprite.x, sprite.y, static_cast<uint32_t>(render.sprite_C), true );

            //clip
            if( locatedP2.x < camCoords.x || coords.x > camLocatedP2.x ||
                locatedP2.y < camCoords.y || coords.y > camLocatedP2.y ) return;

            auto cam_coords { screen_coords - camScreenCoords }; //CAM   COORDS
            engine->drawRect( cam_coords.x, cam_coords.y, sprite.x, sprite.y, static_cast<uint32_t>(render.sprite_C), true );            

            drawFacing(mov, render, camScreenCoords);

            if(debug_mode)
                draw_debug(mov, render, collider2D, camScreenCoords);
    });

    std::for_each(cbegin(textCmps), cend(textCmps), 
        [&](const TextCmp_t& text) {
                  auto& mov        = context.template getCmpByEntityID<MovementComponent>( text.getEntityID() );
            const auto& collider2D = context.template getCmpByEntityID<Collider2DCmp>( text.getEntityID() );

            const auto& coords     { mov.coords };
            const auto& p2         { collider2D.p2 };
            const auto  locatedP2  { coords + p2 };

            auto uP2_x { static_cast<uint32_t>(p2.x.getNoScaled()) };
            auto uP2_y { static_cast<uint32_t>(p2.y.getNoScaled()) };

            auto screen_coords { continuousToScreen(coords) }; //WORLD COORDS 
            auto cam_coords    { screen_coords - camScreenCoords }; //CAM   COORDS

            engine->drawInMinimap( screen_coords.x, screen_coords.y, uP2_x, uP2_y, static_cast<uint32_t>(Color::Blue2), false );

            //clip
            if( locatedP2.x < camCoords.x || coords.x > camLocatedP2.x ||
                locatedP2.y < camCoords.y || coords.y > camLocatedP2.y ) return;

            engine->drawMsg(cam_coords.x, cam_coords.y, uP2_x, uP2_y, text.text.c_str());
    });

           engine->drawInMinimap( camScreenCoords.x, camScreenCoords.y, 
                                  static_cast<uint32_t>(camP2.x.getNoScaled()), static_cast<uint32_t>(camP2.y.getNoScaled()), 
                                  static_cast<uint32_t>(Color::Yellw), false );

           engine->render();
    return engine->shouldClose();
}

//DRAW FUNCTS
template <typename Context_t>
void
RenderSystem<Context_t>::drawFacing(const MovementComponent& mov, const RenderComponent& render, vec2<uint32_t>& camScreenCoords) noexcept {
    auto& sprite      = render.sprite;
    auto  head        { sprite/4 }; 
    auto  h_sp        { sprite/2 }; 
    auto  orientation { mov.orientation };
    
    orientation.x.number *= h_sp.x; //casteo implicito.
    orientation.y.number *= h_sp.y;
    orientation          += mov.coords; 

    auto screen_coords  = continuousToScreen(orientation);
         screen_coords += h_sp - head/2;

    auto cam_coords { screen_coords - camScreenCoords }; //CAM   COORDS
    engine->drawRect(cam_coords.x, cam_coords.y, head.x, head.y, static_cast<uint32_t>(Color::White), true);
}

template <typename Context_t>
void
RenderSystem<Context_t>::drawInterface(Context_t& context) noexcept {
    auto& control = context.template getSCmpByType<InterfaceControl>();
    auto& team    = context.template getCmpByEntityID<TeamComponent>( context.getPlayerID() );

    auto act { static_cast<uint32_t>(team.action) };
    auto frm { static_cast<uint32_t>(team.current_form) };

    engine->modeInterface( act, frm );

    team.action       = static_cast<AI_behaviour>(act);
    team.current_form = static_cast<Formation>(frm);

    if( control.showDebug )
        engine->debugInterface(debug_mode, control.deltaTime, control.deltaSize, control.changed);
}


//AUX
template <typename Context_t>
vec2<uint32_t>
RenderSystem<Context_t>::continuousToScreen(const fvec2<fint_t<int64_t>>& cont) noexcept {
    auto new_x = static_cast<uint32_t>( cont.x.getNoScaled() + HALF_WORLD_W );
    auto new_y = static_cast<uint32_t>( cont.y.getNoScaled() + HALF_WORLD_H );

    return vec2<uint32_t> { new_x, new_y };
}

template <typename Context_t>
vec2<uint32_t> 
RenderSystem<Context_t>::clipToDraw(fvec2<fint_t<int64_t>> point) noexcept {
    point.x = std::clamp(point.x, FIXED_HALF_WORLD_W_N, FIXED_HALF_WORLD_W);
    point.y = std::clamp(point.y, FIXED_HALF_WORLD_H_N, FIXED_HALF_WORLD_H);
    
    return continuousToScreen(point);
}


//DRAW LINES DEBUG
template <typename Context_t>
void
RenderSystem<Context_t>::draw_debug(MovementComponent& mov, const RenderComponent& render, const Collider2DCmp& coll2D, vec2<uint32_t>& camScreenCoords) noexcept {
    //const auto& dir   = mov.dir;
    auto& accel = mov.acc_copy_to_draw;
    auto& separ = mov.sep_copy_to_draw;
    auto& cohes = mov.coh_copy_to_draw;
    
    //ajustamos el inicio de los vectores de steer.
    auto p_ini         = mov.coords;
         p_ini.x      += ( static_cast<int64_t>(render.sprite.x) / 2 );
         p_ini.y      += ( static_cast<int64_t>(render.sprite.y) / 2 );
    auto screen_p_ini  = continuousToScreen(p_ini);
         screen_p_ini -= camScreenCoords;

    vec2<uint32_t> screen_p_end { };

/* 
    if(dir.length2().number != 0) {
        const auto locaterdDir { p_ini + dir }; 
        screen_p_end  = continuousToScreen(locaterdDir);
        screen_p_end -= camScreenCoords;
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_end.x, screen_p_end.y, static_cast<uint32_t>(Color::White));
    }
*/
    if(accel.length2().number != 0) {
        accel        += p_ini;
        screen_p_end  = continuousToScreen(accel);
        screen_p_end -= camScreenCoords;
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_end.x, screen_p_end.y, static_cast<uint32_t>(Color::Green));
    }

    if(separ.length2().number != 0) {
        separ        += p_ini;
        screen_p_end  = continuousToScreen(separ);
        screen_p_end -= camScreenCoords;
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_end.x, screen_p_end.y, static_cast<uint32_t>(Color::Blue));
    }

    if(cohes.length2().number != 0) {
        cohes        += p_ini;
        screen_p_end  = continuousToScreen(cohes);
        screen_p_end -= camScreenCoords;
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_end.x, screen_p_end.y, static_cast<uint32_t>(Color::Red));
    }

// Colliders2DCmp_t
    auto uSize_x  { static_cast<uint32_t>( coll2D.p2.x.getNoScaled() ) };
    auto uSize_y  { static_cast<uint32_t>( coll2D.p2.y.getNoScaled() ) };
    screen_p_ini  = continuousToScreen(mov.coords);
    screen_p_ini -= camScreenCoords;

    engine->drawRect(screen_p_ini.x, screen_p_ini.y, uSize_x, uSize_y, static_cast<uint32_t>(Color::Purple), false);

}


} //NS