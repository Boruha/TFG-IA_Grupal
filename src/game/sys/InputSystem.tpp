#include <game/sys/InputSystem.hpp>
#include <game/cmp/InputComponent.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/AI_Component.hpp>
#include <game/cmp/TeamComponent.hpp>
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
InputSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& input_cmp_vec = context.template getComponentVector<InputComponent>();

    if( ptc_process_events() ) //ESC = 1;
        return false;

    //FPS control
    if( keyboard.isKeyPressed(XK_z) )
        fps_msg.emplace(FPS_Opc::LoopTime, true);

    if( keyboard.isKeyPressed(XK_x) )
        fps_msg.emplace(FPS_Opc::LoopTime, false);

    std::for_each(begin(input_cmp_vec), end(input_cmp_vec), 
        [&](InputComponent& input_cmp) {
            auto& mov = context.template getCmpByEntityID<MovementComponent>( input_cmp.getEntityID() );
            auto& dir   = mov.dir;
            auto& accel = mov.accel_to_target;
            
            fvec2<fint_t<int64_t>> target_dir { };
    
            if( keyboard.isKeyPressed(input_cmp.key_Up) )
                target_dir.y -= ENT_MAX_SPEED;
    
            if( keyboard.isKeyPressed(input_cmp.key_Down) )
                target_dir.y += ENT_MAX_SPEED;
            
            if( keyboard.isKeyPressed(input_cmp.key_Left) )
                target_dir.x -= ENT_MAX_SPEED;
            
            if( keyboard.isKeyPressed(input_cmp.key_Right) )
                target_dir.x += ENT_MAX_SPEED;

            if( keyboard.isKeyPressed(input_cmp.key_b) )
                comand_msg.emplace(AI_behaviour::follow_b);

            if( keyboard.isKeyPressed(input_cmp.key_space) )
                comand_msg.emplace(AI_behaviour::chase_b);
            
            if( keyboard.isKeyPressed(input_cmp.key_0) ) {
                auto& team_cmp        = context.template getCmpByEntityID<TeamComponent>( input_cmp.getEntityID() );
                team_cmp.current_form = Formation::no_form;
            }

            if( keyboard.isKeyPressed(input_cmp.key_1) ) {
                auto& team_cmp        = context.template getCmpByEntityID<TeamComponent>( input_cmp.getEntityID() );
                team_cmp.current_form = Formation::follow_form;
            }

            if( keyboard.isKeyPressed(input_cmp.key_2) ) {
                auto& team_cmp        = context.template getCmpByEntityID<TeamComponent>( input_cmp.getEntityID() );
                team_cmp.current_form = Formation::ring_form;
            }

            target_dir.normalize();
            target_dir *= ENT_MAX_SPEED;

            accel  = (target_dir - dir);
            accel /= ENT_TIME_TO_TARGET;

            if(accel.length2() > ENT_MAX_ACCEL2) {
                accel.normalize();
                accel *= ENT_MAX_ACCEL;
            }
    });

    return true;
}

}