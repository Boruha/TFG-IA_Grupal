#include <sys/InputSystem.hpp>

#include <man/Manager_t.hpp>

#include <cmp/InputComponent.hpp>
#include <cmp/MovementComponent.hpp>
#include <cmp/AI_Component.hpp>

#include <ent/Entity_t.hpp>

#include <utils/AI_Constants.hpp>

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
InputSystem::update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept {
    auto& input_cmp_vec = context->getInputCmps();

    if( ptc_process_events() )
        return false;
    
    if( keyboard.isKeyPressed(XK_0) ) {
        auto& ai_cmp_vec = context->getAI_Cmps();

        std::for_each(ai_cmp_vec.begin(), ai_cmp_vec.end(), 
            [](std::unique_ptr<AI_Component>& ai_cmp) {
            ai_cmp->current_behavior = AI_behaviour::no_b;
        });
    }

    if( keyboard.isKeyPressed(XK_1) ) {
        auto& ai_cmp_vec = context->getAI_Cmps();

        std::for_each(ai_cmp_vec.begin(), ai_cmp_vec.end(), 
            [](std::unique_ptr<AI_Component>& ai_cmp) {
            ai_cmp->current_behavior = AI_behaviour::patrol_b;
        });
    }

    if( keyboard.isKeyPressed(XK_2) ) {
        auto& ai_cmp_vec = context->getAI_Cmps();

        std::for_each(ai_cmp_vec.begin(), ai_cmp_vec.end(), 
            [](std::unique_ptr<AI_Component>& ai_cmp) {
            ai_cmp->current_behavior = AI_behaviour::chase_b;
        });
    }

    if( keyboard.isKeyPressed(XK_3) ) {
        auto& ai_cmp_vec = context->getAI_Cmps();

        std::for_each(ai_cmp_vec.begin(), ai_cmp_vec.end(), 
            [](std::unique_ptr<AI_Component>& ai_cmp) {
            ai_cmp->current_behavior = AI_behaviour::runaway_b;
        });
    }

    if( keyboard.isKeyPressed(XK_4) ) {
        auto& ai_cmp_vec = context->getAI_Cmps();

        std::for_each(ai_cmp_vec.begin(), ai_cmp_vec.end(), 
            [](std::unique_ptr<AI_Component>& ai_cmp) {
            ai_cmp->current_behavior = AI_behaviour::pursue_b;
        });
    }


    std::for_each(begin(input_cmp_vec), end(input_cmp_vec), 
        [&](std::unique_ptr<InputComponent>& input_cmp) {
            auto& ent = context->getEntityByID(input_cmp->getEntityID());
            auto* mov = ent->getComponent<MovementComponent>();
            auto& dir = mov->dir;
            
            dir.x.number = dir.y.number = 0;
    
            if( keyboard.isKeyPressed(input_cmp->key_Up) )
                dir.y -= ENT_MAX_SPEED;
    
            if( keyboard.isKeyPressed(input_cmp->key_Down) )
                dir.y += ENT_MAX_SPEED;
            
            if( keyboard.isKeyPressed(input_cmp->key_Left) )
                dir.x -= ENT_MAX_SPEED;
            
            if( keyboard.isKeyPressed(input_cmp->key_Right) )
                dir.x += ENT_MAX_SPEED;
    });

    return true;
}

}