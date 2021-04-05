#include <game/sys/RenderSystem.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/Collider2DCmp.hpp>
#include <game/cmp/InterfaceControl.hpp>
#include <game/utils/ScreenData.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {
template <typename Context_t>    
RenderSystem<Context_t>::RenderSystem(const uint32_t w, const uint32_t h)
    : engine( std::make_unique<eGL::EngineManager>(w, h, "Prototype_IA") ) { }

//LOOP
template <typename Context_t>
bool
RenderSystem<Context_t>::update(Context_t& context) noexcept {    
    const auto& render_cmp_vec = context.template getComponentVector<RenderComponent>();
          auto& control        = context.template getSCmpByType<InterfaceControl>();
          auto& team           = context.template getCmpByEntityID<TeamComponent>( context.getPlayerID() );


    engine->start_frame();
    engine->minimap();
    //selections
    auto act { static_cast<uint32_t>(team.action) };
    auto frm { static_cast<uint32_t>(team.current_form) };
    engine->modeInterface( act, frm );
    team.action       = static_cast<AI_behaviour>(act);
    team.current_form = static_cast<Formation>(frm);

    if( control.showDebug )
        engine->debugInterface(debug_mode, control.deltaTime, control.deltaSize, control.changed);
    
    std::for_each(cbegin(render_cmp_vec), cend(render_cmp_vec), 
        [&](const RenderComponent& render) {
            auto& mov = context.template getCmpByEntityID<MovementComponent>( render.getEntityID() );
            
            //draw sprite
            auto  screen_coords { continuous_to_screen(mov.coords) };
            auto& sprite        = render.sprite;

            engine->drawRect( screen_coords.x, screen_coords.y, sprite.x, sprite.y, static_cast<uint32_t>(render.sprite_C), true );
            engine->drawInMinimap( screen_coords.x, screen_coords.y, sprite.x, sprite.y, static_cast<uint32_t>(render.sprite_C) );

            auto head        { sprite/4 }; 
            auto h_sp        { sprite/2 }; 
            auto orientation { mov.orientation };
            
            //orientation.normalize();
            
            orientation.x.number *= h_sp.x;
            orientation.y.number *= h_sp.y;
            orientation          += mov.coords; 

            screen_coords  = continuous_to_screen(orientation);
            screen_coords += h_sp - head/2;
        
            engine->drawRect(screen_coords.x, screen_coords.y, head.x, head.y, static_cast<uint32_t>(Color::White), true);

            if(debug_mode) {
                auto& collider2D = context.template getCmpByEntityID<Collider2DCmp>( render.getEntityID() );
                draw_debug(mov, render, collider2D);
            }
    });

           engine->render();
    return engine->shouldClose();
}


//AUX
template <typename Context_t>
vec2<uint32_t>
RenderSystem<Context_t>::continuous_to_screen(const fvec2<fint_t<int64_t>>& cont) noexcept {
    auto new_x = static_cast<uint32_t>( cont.x.getNoScaled() + H_WINDOW_W );
    auto new_y = static_cast<uint32_t>( cont.y.getNoScaled() + H_WINDOW_H );

    return vec2<uint32_t> { new_x, new_y };
}

template <typename Context_t>
vec2<uint32_t> 
RenderSystem<Context_t>::clip_2_draw(fvec2<fint_t<int64_t>> point) noexcept {
    point.x = std::clamp(point.x, (F_H_WINDOW_W_N), F_H_WINDOW_W);
    point.y = std::clamp(point.y, (F_H_WINDOW_H_N), F_H_WINDOW_H);
    
    return continuous_to_screen(point);
}


//DRAW LINES DEBUG
template <typename Context_t>
void
RenderSystem<Context_t>::draw_debug(const MovementComponent& mov, const RenderComponent& render, const Collider2DCmp& coll2D) noexcept {
    //const auto& dir   = mov.dir;
    const auto& accel = mov.acc_copy_to_draw;
    const auto& separ = mov.sep_copy_to_draw;
    const auto& cohes = mov.coh_copy_to_draw;
    
    //ajustamos el inicio de los vectores de steer.
          auto p_ini         = mov.coords;
               p_ini.x      += ( static_cast<int64_t>(render.sprite.x) / 2 );
               p_ini.y      += ( static_cast<int64_t>(render.sprite.y) / 2 );
    const auto screen_p_ini  = clip_2_draw(p_ini);

/*   
    if(dir.length2().number != 0) {
        const auto screen_p_end = clip_2_draw(p_ini + dir);
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_end.x, screen_p_end.y, static_cast<uint32_t>(Color::White));
    }
*/
    if(accel.length2().number != 0) {
        const auto screen_p_end = clip_2_draw(p_ini + accel);
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_end.x, screen_p_end.y, static_cast<uint32_t>(Color::Green));
    }

    if(separ.length2().number != 0) {
        const auto screen_p_end = clip_2_draw(p_ini + separ);
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_end.x, screen_p_end.y, static_cast<uint32_t>(Color::Blue));
    }

    if(cohes.length2().number != 0) {
        const auto screen_p_end = clip_2_draw(p_ini + cohes);
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_end.x, screen_p_end.y, static_cast<uint32_t>(Color::Red));
    }

// Colliders2DCmp_t
    auto uSize         { static_cast<uint32_t>( coll2D.size.getNoScaled() ) };
    auto screen_coords { continuous_to_screen(mov.coords) };

    engine->drawRect(screen_coords.x, screen_coords.y, uSize, uSize, static_cast<uint32_t>(Color::Purple), false);

}


} //NS