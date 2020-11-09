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
InputSystem::update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept {
    auto& input_cmp_vec = context->getInputCmps();

    if( ptc_process_events() )
        return false;

/*
    if(keyboard.isKeyPressed(XK_5)) {
        auto& flocks = context->getFlocks();

        for(auto& flock : flocks) {
            flock->current_behaviour = Flock_behaviour::evade_b;
            flock->current_target = { 0u, 0u };
            flock->target_index = 0u;
            flock->target_list.clear();
        }
    }

    if(keyboard.isKeyPressed(XK_4)) {
        auto& flocks = context->getFlocks();

        for(auto& flock : flocks) {
            flock->current_behaviour = Flock_behaviour::pursue_b;
            flock->current_target = { 0u, 0u };
            flock->target_index = 0u;
            flock->target_list.clear();
        }
    }

    if(keyboard.isKeyPressed(XK_2)) {
        auto& flocks = context->getFlocks();

        for(auto& flock : flocks) {
            flock->current_behaviour = Flock_behaviour::arrive_b;
            ufixed_vec2 new_target { 400u, 400u };
            flock->setTarget(new_target);
        }
    }

    if(keyboard.isKeyPressed(XK_1)) {
        auto& flocks = context->getFlocks();

        for(auto& flock : flocks) {
            flock->current_behaviour = Flock_behaviour::patrol_b;
            std::vector<ufixed_vec2> new_patrol { ufixed_vec2(100u, 100u), ufixed_vec2(600u, 100u)
                                                , ufixed_vec2(600u,600u), ufixed_vec2(100u,600u) };
            flock->setTarget(new_patrol);
        }
    }

    if(keyboard.isKeyPressed(XK_0)) {
        auto& flocks = context->getFlocks();

        for(auto& flock : flocks) 
            flock->current_behaviour = Flock_behaviour::no_b;
    }
*/


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

    };
    
    std::for_each(begin(input_cmp_vec), end(input_cmp_vec), checkKeys);

    return true;
}

}