#include <sys/RenderSystem.hpp>

#include <utils/Color.hpp>

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
    : window_w(w), window_h(h), framebuffer_size(w*h), framebuffer(std::make_unique<uint32_t[]>(w*h)) {
    ptc_open("AI Prototype", window_w, window_h);
    
    auto screen_ptr = framebuffer.get();
    std::fill(screen_ptr, screen_ptr + framebuffer_size, static_cast<uint32_t>(Color::Black));
}

RenderSystem::~RenderSystem() {
    ptc_close();
}

void
RenderSystem::init() noexcept {

}

bool
RenderSystem::update(std::unique_ptr<Manager_t>& context) noexcept {

    const auto& render_cmp_vec = context->getRenderCmps();
          auto* screen_ptr     = framebuffer.get();

    std::fill(screen_ptr, screen_ptr + framebuffer_size, static_cast<uint32_t>(Color::Black));

    auto drawSprite = [&](const std::unique_ptr<RenderComponent>& render_cmp) {
        auto& ent     = context->getEntityByID(render_cmp->getEntityID());
        auto* mov_cmp = ent->getComponent<MovementComponent>();

        auto* screen_ptr  = framebuffer.get();
              screen_ptr += (mov_cmp->coord_Y * window_w) + mov_cmp->coord_X;

        for(uint32_t i=0; i<render_cmp->sprite_H; ++i) {
            std::fill(screen_ptr, screen_ptr + render_cmp->sprite_W, static_cast<uint32_t>(render_cmp->sprite_C));
            screen_ptr += window_w;
        }
    };

    std::for_each(cbegin(render_cmp_vec), cend(render_cmp_vec), drawSprite);  

    ptc_update(screen_ptr);

    return !ptc_process_events();
}

} //NS