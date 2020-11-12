#include <sys/InputSystem.hpp>

#include <man/Manager_t.hpp>

#include <cmp/InputComponent.hpp>
#include <cmp/MovementComponent.hpp>

#include <ent/Entity_t.hpp>

extern "C" {
  #include "tinyPTC/tinyptc.h"  
}

#include <algorithm>


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
InputSystem::update(const std::unique_ptr<Manager_t>& context, const fixed32_t DeltaTime) noexcept {
    auto& input_cmp_vec = context->getInputCmps();

    if( ptc_process_events() )
        return false;

    auto checkKeys = [&](std::unique_ptr<InputComponent>& input_cmp) {
        auto& ent = context->getEntityByID(input_cmp->getEntityID());
        auto* mov = ent->getComponent<MovementComponent>();
        auto& dir = mov->dir;
        
        dir.x.number = dir.y.number = 0;

        if( keyboard.isKeyPressed(input_cmp->key_Up) )
            dir.y.number -= SCALE_S;

        if( keyboard.isKeyPressed(input_cmp->key_Down) )
            dir.y.number += SCALE_S;
        
        if( keyboard.isKeyPressed(input_cmp->key_Left) )
            dir.x.number -= SCALE_S;
        
        if( keyboard.isKeyPressed(input_cmp->key_Right) )
            dir.x.number += SCALE_S;

        dir.normalize();

    };
    
    std::for_each(begin(input_cmp_vec), end(input_cmp_vec), checkKeys);

    return true;
}

}