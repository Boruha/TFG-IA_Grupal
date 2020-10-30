#include <sys/InputSystem.hpp>

#include <man/Manager_t.hpp>

#include <cmp/RenderComponent.hpp>

extern "C" {
  #include "tinyPTC/tinyptc.h"  
}

#include <iostream>

namespace AIP {

void 
InputSystem::onkeypress(KeySym key) {
    keyboard.setValue(key, true);
}

void 
InputSystem::onkeyrelease(KeySym key) {
    keyboard.setValue(key, false);
}

InputSystem::InputSystem() {
    ptc_set_on_keypress( onkeypress );
    ptc_set_on_keyrelease( onkeyrelease );
}

void 
InputSystem::init() noexcept { }

bool 
InputSystem::update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept {
    ptc_process_events();

    if(keyboard.isKeyPressed( XK_b )) {
        auto& render_cmp_vec = context->getRenderCmps();

        for(auto& render_cmp : render_cmp_vec) {
            render_cmp->sprite_C = Color::Blue;
        }
    }
        

    return true;
}

}