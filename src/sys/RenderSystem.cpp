#include <sys/RenderSystem.hpp>
#include <utils/Color.hpp>
#include <man/Manager_t.hpp>

extern "C" {
  #include "tinyPTC/tinyptc.h"  
}

#include <ent/Entity_t.hpp>

namespace AIP {

RenderSystem::RenderSystem(const uint32_t w, const uint32_t h) 
: window_w(w), window_h(h), framebuffer_size(w*h), framebuffer(std::make_unique<uint32_t[]>(w*h)) {
    ptc_open("AI Prototype", window_w, window_h);
    
    auto screen_ptr = framebuffer.get();
    std::fill(screen_ptr, screen_ptr + framebuffer_size, static_cast<uint32_t>(Color::White));
}

RenderSystem::~RenderSystem() {
    ptc_close();
}

void
RenderSystem::init() {

}

bool
RenderSystem::update(const std::unique_ptr<Manager_t>& context) {

    auto& ent_vec_ref = context->getEntities();
    auto* screen_ptr  = framebuffer.get();

    std::fill(screen_ptr, screen_ptr + framebuffer_size, static_cast<uint32_t>(Color::White));

    for(const auto& entity : ent_vec_ref)
        drawEntity(entity);        

    ptc_update(screen_ptr);

    return !ptc_process_events();
}

void
RenderSystem::drawEntity(const std::unique_ptr<Entity_t>& entity) const {
    auto* screen_ptr = framebuffer.get();

    screen_ptr += (entity->coord_Y * window_w) + entity->coord_X;

    for(uint32_t i=0; i<entity->sprite_H; ++i) {
        std::fill(screen_ptr, screen_ptr + entity->sprite_W, static_cast<uint32_t>(entity->sprite_C));
        screen_ptr += window_w;
    }
}

} //NS