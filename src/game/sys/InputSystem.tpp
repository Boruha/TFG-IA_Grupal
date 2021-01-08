#include <game/sys/InputSystem.hpp>
#include <game/cmp/InputComponent.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/AI_Component.hpp> //ONLY TEST TEST TEST TEST
#include <game/utils/AI_Constants.hpp>

#include <ecs/ent/Entity_t.hpp>


extern "C" {
  #include "tinyPTC/tinyptc.h"  
}

#include <algorithm>

namespace AIP {

template <typename Context_t>
void 
InputSystem<Context_t>::onkeypress(KeySym key) {
    keyboard.setValue(key, true);
}

template <typename Context_t>
void 
InputSystem<Context_t>::onkeyrelease(KeySym key) {
    keyboard.setValue(key, false);
}

template <typename Context_t>
InputSystem<Context_t>::InputSystem() {
    ptc_set_on_keypress( onkeypress );
    ptc_set_on_keyrelease( onkeyrelease );
}

template <typename Context_t>
bool 
InputSystem<Context_t>::update(Context_t& context, const fixed64_t DeltaTime) noexcept {
    auto& input_cmp_vec = context.template getComponentVector<InputComponent>();

    if( ptc_process_events() ) //ESC = 1;
        return false;

     if( keyboard.isKeyPressed(XK_Control_L) ) {
                auto& ai_vec = context.template getComponentVector<AI_Component>();
                if( !ai_vec.empty() )
                    context.deleteEntity( ai_vec.front().getEntityID() );
     }

    std::for_each(begin(input_cmp_vec), end(input_cmp_vec), 
        [&](InputComponent& input_cmp) {
            auto& mov = context.template getCmpByEntityID<MovementComponent>( input_cmp.getEntityID() );
            auto& dir = mov.dir;
            
            dir.x.number = dir.y.number = 0;
    
            if( keyboard.isKeyPressed(input_cmp.key_Up) )
                dir.y -= ENT_MAX_SPEED;
    
            if( keyboard.isKeyPressed(input_cmp.key_Down) )
                dir.y += ENT_MAX_SPEED;
            
            if( keyboard.isKeyPressed(input_cmp.key_Left) )
                dir.x -= ENT_MAX_SPEED;
            
            if( keyboard.isKeyPressed(input_cmp.key_Right) )
                dir.x += ENT_MAX_SPEED;
    });

    return true;
}

}