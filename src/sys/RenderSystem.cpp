#include <sys/RenderSystem.hpp>

#include <man/Manager_t.hpp>

#include <ent/Entity_t.hpp>

#include <cmp/RenderComponent.hpp>
#include <cmp/MovementComponent.hpp>

extern "C" {
  #include "tinyPTC/tinyptc.h"  
}

#include <algorithm>

namespace AIP {

RenderSystem::RenderSystem(const uint32_t w, const uint32_t h) 
    : window_w(w), window_h(h), half_window_w(w/2), half_window_h(h/2), framebuffer_size(w*h), framebuffer(std::make_unique<uint32_t[]>(w*h)) {
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
RenderSystem::update(const std::unique_ptr<Manager_t>& context, const fixed32_t DeltaTime) noexcept {
    const auto& render_cmp_vec = context->getRenderCmps();
          auto* screen_ptr     = framebuffer.get();

    std::fill(screen_ptr, screen_ptr + framebuffer_size, static_cast<uint32_t>(Color::Black));

    auto drawSprite = [&](const std::unique_ptr<RenderComponent>& render_cmp) {
              auto& ent     = context->getEntityByID(render_cmp->getEntityID());
        const auto* mov_cmp = ent->getComponent<MovementComponent>();
        
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


} //NS