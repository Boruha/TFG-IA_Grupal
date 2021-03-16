#include <game/sys/RenderSystem.hpp>
#include <game/cmp/MovementComponent.hpp>
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
RenderSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {    
    const auto& render_cmp_vec = context.template getComponentVector<RenderComponent>();
          auto& control        = context.template getSCmpByType<InterfaceControl>();

    engine->start_frame();

    if( control.showDebug )
        engine->debugInterface(debug_mode, control.deltaTime, control.deltaSize, control.changed);

    engine->minimap();

    std::for_each(cbegin(render_cmp_vec), cend(render_cmp_vec), 
        [&](const RenderComponent& render_cmp) {
            auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>( render_cmp.getEntityID() );
            
            //draw sprite
            auto  screen_coords { continuous_to_screen(mov_cmp.coords) };
            vec2  sprite        = render_cmp.sprite;

            engine->drawRectFilled(screen_coords.x, screen_coords.y, sprite.x, sprite.y, static_cast<uint32_t>(render_cmp.sprite_C) );
            engine->drawInMinimap( screen_coords.x, screen_coords.y, sprite.x, sprite.y, static_cast<uint32_t>(render_cmp.sprite_C) );

            auto head         { sprite/4 }; 
            auto h_sp         { sprite/2 }; 
            auto orientation  { mov_cmp.orientation };
            
            orientation.normalize();
            
            orientation.x.number *= h_sp.x;
            orientation.y.number *= h_sp.y;
            orientation          += mov_cmp.coords; 

            screen_coords  = continuous_to_screen(orientation);
            screen_coords += h_sp - head/2;
        
            engine->drawRectFilled(screen_coords.x, screen_coords.y, head.x, head.y, static_cast<uint32_t>(Color::White));

            if(debug_mode)
                draw_debug(mov_cmp, render_cmp);
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
    point.x         = std::clamp(point.x, (F_H_WINDOW_W_N), F_H_WINDOW_W);
    point.y         = std::clamp(point.y, (F_H_WINDOW_H_N), F_H_WINDOW_H);
    
    return continuous_to_screen(point);
}

//DRAW LINES DEBUG
template <typename Context_t>
void
RenderSystem<Context_t>::draw_debug(const MovementComponent& mov_cmp, const RenderComponent& render_cmp) noexcept {
    //const auto& dir   = mov_cmp.dir;
    const auto& accel = mov_cmp.acc_copy_to_draw;
    const auto& separ = mov_cmp.sep_copy_to_draw;
    const auto& cohes = mov_cmp.coh_copy_to_draw;
    
    //ajustamos el inicio de los vectores de steer.
          auto p_ini         = mov_cmp.coords;
               p_ini.x      += ( static_cast<int64_t>(render_cmp.sprite.x) / 2 );
               p_ini.y      += ( static_cast<int64_t>(render_cmp.sprite.y) / 2 );
    const auto screen_p_ini  = clip_2_draw(p_ini);
/*   
    if(dir.length2().number != 0) {
        const auto screen_p_fin = clip_2_draw(p_ini + dir);
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_fin.x, screen_p_fin.y, static_cast<uint32_t>(Color::White));
    }
*/
    if(accel.length2().number != 0) {
        const auto screen_p_fin = clip_2_draw(p_ini + accel);
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_fin.x, screen_p_fin.y, static_cast<uint32_t>(Color::Green));
    }

    if(separ.length2().number != 0) {
        const auto screen_p_fin = clip_2_draw(p_ini + separ);
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_fin.x, screen_p_fin.y, static_cast<uint32_t>(Color::Blue));
    }

    if(cohes.length2().number != 0) {
        const auto screen_p_fin = clip_2_draw(p_ini + cohes);
        engine->drawLine(screen_p_ini.x, screen_p_ini.y, screen_p_fin.x, screen_p_fin.y, static_cast<uint32_t>(Color::Red));
    }
}


} //NS