#include <game/sys/RenderSystem.hpp>
#include <game/cmp/MovementComponent.hpp>

#include <ecs/ent/Entity_t.hpp>


extern "C" {
  #include "tinyPTC/tinyptc.h"
}

#include <algorithm>
#include <iostream>

namespace AIP {

//CTOR / DTOR
template <typename Context_t>    
RenderSystem<Context_t>::RenderSystem(const uint32_t w, const uint32_t h)
    : window_w(w), window_h(h), half_window_w(w/2), half_window_h(h/2), framebuffer_size(w*h)
    , half_window_w64( static_cast<int64_t>(w/2) ), half_window_h64( static_cast<int64_t>(h/2) )
    , framebuffer( std::make_unique<uint32_t[]>(w*h) ) {

    ptc_open("AI Prototype", window_w, window_h);
    
    auto screen_ptr = framebuffer.get();
    std::fill(screen_ptr, screen_ptr + framebuffer_size, static_cast<uint32_t>(Color::Black));
}

template <typename Context_t>   
RenderSystem<Context_t>::~RenderSystem() {
    ptc_close();
}

//LOOP
template <typename Context_t>
bool
RenderSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {    
    const auto& render_cmp_vec = context.template getComponentVector<RenderComponent>();
          auto* screen_ptr     = framebuffer.get();

    //clean de pantalla
    std::fill(screen_ptr, screen_ptr + framebuffer_size, static_cast<uint32_t>(Color::Black));

    //pintar todos los render_cmp
    std::for_each(cbegin(render_cmp_vec), cend(render_cmp_vec), 
        [&](const RenderComponent& render_cmp) {
            auto& mov_cmp = context.template getCmpByEntityID<MovementComponent>( render_cmp.getEntityID() );

            //paso de continuo a pixel
            const auto screen_coords  = continuous_to_screen(mov_cmp.coords);

            //puntero a posicion al sprite.
            auto* screen_pos  = framebuffer.get();
                  screen_pos += (screen_coords.y * window_w) + screen_coords.x;

            //pintar sprite
            for(uint32_t i=0; i<render_cmp.sprite.y.getNoScaled(); ++i) {
                std::fill(screen_pos, screen_pos + render_cmp.sprite.y.getNoScaled(), static_cast<uint32_t>(render_cmp.sprite_C));
                screen_pos += window_w;
            }

            if(debug_mode)
                draw_debug(mov_cmp, render_cmp);

    });

    ptc_update(screen_ptr);

    return true;
}

//AUX
template <typename Context_t>
vec2<uint32_t>
RenderSystem<Context_t>::continuous_to_screen(const fvec2<fint_t<int64_t>>& cont) noexcept {
    auto new_x = static_cast<uint32_t>( cont.x.getNoScaled() + half_window_w );
    auto new_y = static_cast<uint32_t>( cont.y.getNoScaled() + half_window_h );

    return vec2<uint32_t> { new_x, new_y };
}


//DRAW LINES DEBUG
template <typename Context_t>
void
RenderSystem<Context_t>::bresenham_line(const vec2<uint32_t>& screen_p_ini, const vec2<uint32_t>& screen_p_fin
                            , int32_t dY, int32_t dX, const Color& color) noexcept {

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
RenderSystem<Context_t>::draw_debug(const MovementComponent& mov_cmp, const RenderComponent& render_cmp) noexcept {
    const auto& dir   = mov_cmp.dir;
    const auto& accel = mov_cmp.accel_to_target;
    const auto& separ = mov_cmp.sep_copy_to_draw;
    const auto& cohes = mov_cmp.coh_copy_to_draw;
    
    //ajustamos el inicio de los vectores de steer.
    auto p_ini = mov_cmp.coords;
    p_ini.x.number += ( static_cast<int64_t>(render_cmp.sprite.x.number) / 2 );
    p_ini.y.number += ( static_cast<int64_t>(render_cmp.sprite.y.number) / 2 );
    p_ini.x  = std::clamp(p_ini.x, (half_window_w64*-1), half_window_w64);
    p_ini.y  = std::clamp(p_ini.y, (half_window_h64*-1), half_window_h64);
    
    const auto screen_p_ini = continuous_to_screen(p_ini);
    
    if(dir.length2().number != 0) {
        auto p_fin = p_ini + dir;
        p_fin.x = std::clamp(p_fin.x, (half_window_w64*-1), half_window_w64);
        p_fin.y = std::clamp(p_fin.y, (half_window_h64*-1), half_window_h64);

        const auto screen_p_fin = continuous_to_screen(p_fin);

        int32_t dX = screen_p_fin.x - screen_p_ini.x;
        int32_t dY = screen_p_fin.y - screen_p_ini.y;
        bresenham_line(screen_p_ini, screen_p_fin, dY, dX, Color::White);
    }

    if(accel.length2().number != 0) {
        auto p_fin = p_ini + accel;
        p_fin.x = std::clamp(p_fin.x, (half_window_w64*-1), half_window_w64);
        p_fin.y = std::clamp(p_fin.y, (half_window_h64*-1), half_window_h64);

        const auto screen_p_fin = continuous_to_screen(p_fin);

        int32_t dX = screen_p_fin.x - screen_p_ini.x;
        int32_t dY = screen_p_fin.y - screen_p_ini.y;
        bresenham_line(screen_p_ini, screen_p_fin, dY, dX, Color::Green);
    }

    if(separ.length2().number != 0) {
        auto p_fin = p_ini + separ;
        p_fin.x = std::clamp(p_fin.x, (half_window_w64*-1), half_window_w64);
        p_fin.y = std::clamp(p_fin.y, (half_window_h64*-1), half_window_h64);

        const auto screen_p_fin = continuous_to_screen(p_fin);

        int32_t dX = screen_p_fin.x - screen_p_ini.x;
        int32_t dY = screen_p_fin.y - screen_p_ini.y;
        bresenham_line(screen_p_ini, screen_p_fin, dY, dX, Color::Blue);
    }

    if(cohes.length2().number != 0) {
        auto p_fin = p_ini + cohes;
        p_fin.x = std::clamp(p_fin.x, (half_window_w64*-1), half_window_w64);
        p_fin.y = std::clamp(p_fin.y, (half_window_h64*-1), half_window_h64);

        const auto screen_p_fin = continuous_to_screen(p_fin);

        int32_t dX = screen_p_fin.x - screen_p_ini.x;
        int32_t dY = screen_p_fin.y - screen_p_ini.y;
        bresenham_line(screen_p_ini, screen_p_fin, dY, dX, Color::Red);
    }

}

template <typename Context_t>
void
RenderSystem<Context_t>::draw_line_X(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dY, const int32_t dX, const Color& color) noexcept { 
    int32_t iy = window_w;
    uint32_t y_limit = p_ini.y;

    if(dY < 0 ) {
        iy *= -1;
        dY *= -1;
    }

    int32_t D  = 2 * dY - dX;

    auto* screen_ptr  = framebuffer.get();
          screen_ptr += (p_ini.y * window_w) + p_ini.x;
    
    for(uint32_t x = p_ini.x; x < p_end.x; ++x) {
        if(y_limit < window_h) {    
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
RenderSystem<Context_t>::draw_line_Y(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dX, const int32_t dY, const Color& color) noexcept { 
    int32_t ix = 1;
    uint32_t x_limit = p_ini.x;

    if(dX < 0 ) {
        ix *= -1;
        dX *= -1;
    }

    int32_t D  = 2 * dX - dY;

    auto* screen_ptr  = framebuffer.get();
          screen_ptr += (p_ini.y * window_w) + p_ini.x;
    
    for(uint32_t y = p_ini.y; y < p_end.y; ++y) {
        if(x_limit < window_w) {
            *screen_ptr = static_cast<uint32_t>(color);
            
            if(D > 0) {
                screen_ptr += ix;
                ++x_limit;
                D += 2 * (dX - dY);
            }

            D += 2 * dX;
            screen_ptr += window_w;
        }
    }
}

template <typename Context_t>
void
RenderSystem<Context_t>::draw_line_H(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color& color) noexcept { 
    auto* screen_ptr  = framebuffer.get();
          screen_ptr += (p_ini.y * window_w) + p_ini.x;
    
    for(uint32_t x=p_ini.x; x<p_end.x; ++x) {
        *screen_ptr = static_cast<uint32_t>(color);
        ++screen_ptr;
    }
}

template <typename Context_t>
void
RenderSystem<Context_t>::draw_line_V(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color& color) noexcept { 
    auto* screen_ptr  = framebuffer.get();
          screen_ptr += (p_ini.y * window_w) + p_ini.x;
        
    for(uint32_t y=p_ini.y; y<p_end.y; ++y) {
        *screen_ptr = static_cast<uint32_t>(color);
        screen_ptr += window_w;
    }
}

} //NS