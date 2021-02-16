#include <game/sys/RenderSystem.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/utils/ScreenData.hpp>

#include <ecs/ent/Entity_t.hpp>

extern "C" {
  #include "tinyPTC/tinyptc.h"
}

#include <algorithm>
#include <iostream>

namespace AIP {

template <typename Context_t>    
RenderSystem<Context_t>::RenderSystem(const uint32_t w, const uint32_t h)
    : framebuffer_size(w*h), framebuffer( std::make_unique<uint32_t[]>(w*h) ) {

    ptc_open("AI Prototype", w, h);
    clean();
}

template <typename Context_t>   
RenderSystem<Context_t>::~RenderSystem() {
    ptc_close();
}


//LOOP
template <typename Context_t>
void
RenderSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {    
    const auto& render_cmp_vec = context.template getComponentVector<RenderComponent>();

    clean();

    std::for_each(cbegin(render_cmp_vec), cend(render_cmp_vec), 
        [&](const RenderComponent& render_cmp) {
            auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>( render_cmp.getEntityID() );
            
            //draw sprite
            auto  screen_coords  { continuous_to_screen(mov_cmp.coords) };
            auto* screen_ptr     { framebuffer.get() };
                  screen_ptr    += (screen_coords.y * U_WINDOW_W) + screen_coords.x;
            vec2  sprite         = render_cmp.sprite;

            for(uint32_t i=0; i<sprite.y; ++i) {
                std::fill( screen_ptr, screen_ptr + sprite.x, static_cast<uint32_t>(render_cmp.sprite_C) );
                screen_ptr += U_WINDOW_W;
            }

            auto head         { sprite/4 }; 
            auto h_sp         { sprite/2 }; 
            auto orientation  { mov_cmp.orientation };
            
            orientation.normalize();
            
            orientation.x.number  *= h_sp.x;
            orientation.y.number  *= h_sp.y;
            orientation           += mov_cmp.coords; 

            screen_coords  = continuous_to_screen(orientation);
            screen_coords += h_sp - head/2;
        
            screen_ptr  = framebuffer.get();
            screen_ptr += (screen_coords.y * U_WINDOW_W) + screen_coords.x;

            for(uint32_t i=0; i<head.y; ++i) {
                std::fill( screen_ptr, screen_ptr + head.x, static_cast<uint32_t>(Color::White) );
                screen_ptr += U_WINDOW_W;
            }
           
            if(debug_mode)
                draw_debug(mov_cmp, render_cmp);
    });

    ptc_update(framebuffer.get());
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
    
    return this->continuous_to_screen(point);
}

template <typename Context_t>
void
RenderSystem<Context_t>::clean() noexcept {
    auto screen_ptr = framebuffer.get();
    std::fill(screen_ptr, screen_ptr + framebuffer_size, static_cast<uint32_t>(Color::Black));
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

        int32_t dX = screen_p_fin.x - screen_p_ini.x;
        int32_t dY = screen_p_fin.y - screen_p_ini.y;
        bresenham_line(screen_p_ini, screen_p_fin, dY, dX, Color::White);
    }
*/
    if(accel.length2().number != 0) {
        const auto screen_p_fin = clip_2_draw(p_ini + accel);

        int32_t dX = screen_p_fin.x - screen_p_ini.x;
        int32_t dY = screen_p_fin.y - screen_p_ini.y;
        bresenham_line(screen_p_ini, screen_p_fin, dY, dX, Color::Green);
    }

    if(separ.length2().number != 0) {
        const auto screen_p_fin = clip_2_draw(p_ini + separ);

        int32_t dX = screen_p_fin.x - screen_p_ini.x;
        int32_t dY = screen_p_fin.y - screen_p_ini.y;
        bresenham_line(screen_p_ini, screen_p_fin, dY, dX, Color::Blue);
    }

    if(cohes.length2().number != 0) {
        const auto screen_p_fin = clip_2_draw(p_ini + cohes);

        int32_t dX = screen_p_fin.x - screen_p_ini.x;
        int32_t dY = screen_p_fin.y - screen_p_ini.y;
        bresenham_line(screen_p_ini, screen_p_fin, dY, dX, Color::Red);
    }

}

template <typename Context_t>
void
RenderSystem<Context_t>::bresenham_line(const vec2<uint32_t>& screen_p_ini, const vec2<uint32_t>& screen_p_fin, int32_t dY, int32_t dX, const Color color) noexcept {                            
    if( (dX * dX) >= (dY * dY) ) {
        if(dY == 0) {
            if(screen_p_ini.x > screen_p_fin.x)
                draw_line_H(screen_p_fin, screen_p_ini, color);
            else
                draw_line_H(screen_p_ini, screen_p_fin, color);
        }
        else {
            if(screen_p_ini.x > screen_p_fin.x)
                draw_line_X(screen_p_fin, screen_p_ini, -dY, -dX, color);
            else
                draw_line_X(screen_p_ini, screen_p_fin,  dY,  dX, color);
        }
    }
    else {
        if(dX == 0) {
            if(screen_p_ini.y > screen_p_fin.y)
                draw_line_V(screen_p_fin, screen_p_ini, color);
            else
                draw_line_V(screen_p_ini, screen_p_fin, color);
        }
        else {
            if(screen_p_ini.y > screen_p_fin.y)
                draw_line_Y(screen_p_fin, screen_p_ini, -dX, -dY, color);
            else
                draw_line_Y(screen_p_ini, screen_p_fin,  dX,  dY, color);
        }
    }
}

template <typename Context_t>
void
RenderSystem<Context_t>::draw_line_X(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dY, const int32_t dX, const Color color) noexcept { 
    int32_t iy = U_WINDOW_W;
    uint32_t y_limit = p_ini.y;

    if(dY < 0 ) {
        iy *= -1;
        dY *= -1;
    }

    int32_t D  = 2 * dY - dX;

    auto* screen_ptr  = framebuffer.get();
          screen_ptr += (p_ini.y * U_WINDOW_W) + p_ini.x;
    
    for(uint32_t x = p_ini.x; x < p_end.x; ++x) {
        if(y_limit < U_WINDOW_H) {  
            *screen_ptr = static_cast<uint32_t>(color);

            if(D > 0) {
                screen_ptr += iy;
                ++y_limit;
                D += 2 * (dY - dX);
            }

            D += 2 * dY;
            ++screen_ptr;
        }
    }
}

template <typename Context_t>
void
RenderSystem<Context_t>::draw_line_Y(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dX, const int32_t dY, const Color color) noexcept { 
    int32_t ix = 1;
    uint32_t x_limit = p_ini.x;

    if(dX < 0 ) {
        ix *= -1;
        dX *= -1;
    }

    int32_t D  = 2 * dX - dY;

    auto* screen_ptr  = framebuffer.get();
          screen_ptr += (p_ini.y * U_WINDOW_W) + p_ini.x;
    
    for(uint32_t y = p_ini.y; y < p_end.y; ++y) {
        if(x_limit < U_WINDOW_W) {
            *screen_ptr = static_cast<uint32_t>(color);
            
            if(D > 0) {
                screen_ptr += ix;
                ++x_limit;
                D += 2 * (dX - dY);
            }

            D += 2 * dX;
            screen_ptr += U_WINDOW_W;
        }
    }
}

template <typename Context_t>
void
RenderSystem<Context_t>::draw_line_H(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color color) noexcept { 
    auto* screen_ptr  = framebuffer.get();
          screen_ptr += (p_ini.y * U_WINDOW_W) + p_ini.x;
    
    for(uint32_t x=p_ini.x; x<p_end.x; ++x) {
        *screen_ptr = static_cast<uint32_t>(color);
        ++screen_ptr;
    }
}

template <typename Context_t>
void
RenderSystem<Context_t>::draw_line_V(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color color) noexcept { 
    auto* screen_ptr  = framebuffer.get();
          screen_ptr += (p_ini.y * U_WINDOW_W) + p_ini.x;
        
    for(uint32_t y=p_ini.y; y<p_end.y; ++y) {
        *screen_ptr = static_cast<uint32_t>(color);
        screen_ptr += U_WINDOW_W;
    }
}

} //NS