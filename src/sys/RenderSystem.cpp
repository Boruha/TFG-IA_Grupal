#include <sys/RenderSystem.hpp>

#include <man/Manager_t.hpp>

#include <ent/Entity_t.hpp>

#include <cmp/MovementComponent.hpp>

extern "C" {
  #include "tinyPTC/tinyptc.h"  
}

#include <algorithm>
#include <iostream>

namespace AIP {

RenderSystem::RenderSystem(const uint32_t w, const uint32_t h)
    : window_w(w), window_h(h), half_window_w(w/2), half_window_h(h/2), framebuffer_size(w*h)
    , half_window_w64( static_cast<int64_t>(w/2) ), half_window_h64( static_cast<int64_t>(h/2) )
    , framebuffer( std::make_unique<uint32_t[]>(w*h) ) {

    ptc_open("AI Prototype", window_w, window_h);
    
    auto screen_ptr = framebuffer.get();
    std::fill(screen_ptr, screen_ptr + framebuffer_size, static_cast<uint32_t>(Color::Black));
}

RenderSystem::~RenderSystem() {
    ptc_close();
    framebuffer.~unique_ptr();
}

void
RenderSystem::init() noexcept {

}

bool
RenderSystem::update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept {
    const auto& render_cmp_vec = context->getRenderCmps();
          auto* screen_ptr     = framebuffer.get();

    std::fill(screen_ptr, screen_ptr + framebuffer_size, static_cast<uint32_t>(Color::Black));

    auto drawSprite = [&](const std::unique_ptr<RenderComponent>& render_cmp) {
        auto& ent     = context->getEntityByID(render_cmp->getEntityID());
        auto* mov_cmp = ent->getComponent<MovementComponent>();

        //paso de continuo a pixel
        const auto screen_coords  = continuous_to_screen(mov_cmp->coords);

        //puntero a inicio pantalla y colocación para pintar el sprite.
        auto* screen_ptr  = framebuffer.get();
              screen_ptr += (screen_coords.y * window_w) + screen_coords.x;

        //pintar sprite
        for(uint32_t i=0; i<render_cmp->sprite.y.getNoScaled(); ++i) {
            std::fill(screen_ptr, screen_ptr + render_cmp->sprite.y.getNoScaled(), static_cast<uint32_t>(render_cmp->sprite_C));
            screen_ptr += window_w;
        }
        //pintar vector deplazamiento
        bresenham_line(mov_cmp, render_cmp);
    };

    std::for_each(cbegin(render_cmp_vec), cend(render_cmp_vec), drawSprite);

    ptc_update(screen_ptr);

    return true;
}

vec2<uint32_t>
RenderSystem::continuous_to_screen(const fixed_vec2& cont) noexcept {
    auto new_x = static_cast<uint32_t>( cont.x.getNoScaled() + half_window_w );
    auto new_y = static_cast<uint32_t>( cont.y.getNoScaled() + half_window_h );

    return vec2<uint32_t> { new_x, new_y };
}

void
RenderSystem::bresenham_line(MovementComponent* mov_cmp, const std::unique_ptr<RenderComponent>& render_cmp) noexcept {
    auto& dir   = mov_cmp->dir; 
    auto& color = render_cmp->sprite_C;
    
    if(dir.length2().number == 0)
        return;

    auto p_ini = mov_cmp->coords;
    p_ini.x += (static_cast<fixed64_t>(render_cmp->sprite.x)/2);
    p_ini.y += (static_cast<fixed64_t>(render_cmp->sprite.y)/2);
    auto p_fin = p_ini + (dir * mov_cmp->vel);

    p_ini.x = std::clamp(p_ini.x, (half_window_w64*-1), half_window_w64);
    p_ini.y = std::clamp(p_ini.y, (half_window_h64*-1), half_window_h64);
    p_fin.x = std::clamp(p_fin.x, (half_window_w64*-1), half_window_w64);
    p_fin.y = std::clamp(p_fin.y, (half_window_h64*-1), half_window_h64);

    const auto screen_p_ini = continuous_to_screen(p_ini);
    const auto screen_p_fin = continuous_to_screen(p_fin);

    int32_t dX = screen_p_fin.x - screen_p_ini.x;
    int32_t dY = screen_p_fin.y - screen_p_ini.y;

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

void
RenderSystem::draw_line_X(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dY, const int32_t dX, const Color& color) noexcept { 
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

void
RenderSystem::draw_line_Y(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dX, const int32_t dY, const Color& color) noexcept { 
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

void
RenderSystem::draw_line_H(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color& color) noexcept { 
    auto* screen_ptr  = framebuffer.get();
          screen_ptr += (p_ini.y * window_w) + p_ini.x;
    
    for(uint32_t x=p_ini.x; x<p_end.x; ++x) {
        *screen_ptr = static_cast<uint32_t>(color);
        ++screen_ptr;
    }
}

void
RenderSystem::draw_line_V(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color& color) noexcept { 
    auto* screen_ptr  = framebuffer.get();
          screen_ptr += (p_ini.y * window_w) + p_ini.x;
        
    for(uint32_t y=p_ini.y; y<p_end.y; ++y) {
        *screen_ptr = static_cast<uint32_t>(color);
        screen_ptr += window_w;
    }
}

} //NS