#include <sys/RenderSystem.hpp>
#include <utils/Color.hpp>

extern "C" {
  #include "tinyPTC/tinyptc.h"  
}

namespace AIP {

RenderSystem::RenderSystem(const uint32_t w, const uint32_t h) 
: window_w(w), window_h(h), framebuffer_size(w*h), framebuffer(std::make_unique<uint32_t[]>(w*h)) {
    ptc_open("AI Prototype", window_w, window_h);
}

RenderSystem::~RenderSystem() {
    ptc_close();
}

void
RenderSystem::init() {

}

bool
RenderSystem::update() {

    auto screen_ptr = framebuffer.get();

    std::fill(screen_ptr, screen_ptr + framebuffer_size, static_cast<uint32_t>(Color::White));

    ptc_update(screen_ptr);

    return !ptc_process_events();
}



} //NS