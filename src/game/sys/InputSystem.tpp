#include <game/sys/InputSystem.hpp>

#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/AI_Component.hpp>
#include <game/cmp/TeamComponent.hpp>
#include <game/cmp/InterfaceControl.hpp>
#include <game/cmp/EventCmp_t.hpp>
#include <game/utils/AI_Constants.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <engineGL/EngineManager.hpp>

namespace AIP {

template <typename Context_t>
bool 
InputSystem<Context_t>::update(Context_t& context) noexcept {
    auto  pj_id = context.getPlayerID();
    auto& mov   = context.template getCmpByEntityID<MovementComponent>( pj_id );
    auto& team  = context.template getCmpByEntityID<TeamComponent>( pj_id );

    auto& dir   = mov.dir;
    auto& accel = mov.accel_to_target;

    fvec2<fint_t<int64_t>> target_dir { };

    if( ImGui::IsKeyDown(GLFW_KEY_ESCAPE) )
        return false;

    if( ImGui::IsKeyDown(GLFW_KEY_UP) )
        target_dir.y -= ENT_MAX_SPEED;
    
    if( ImGui::IsKeyDown(GLFW_KEY_DOWN) )
        target_dir.y += ENT_MAX_SPEED;
    
    if( ImGui::IsKeyDown(GLFW_KEY_LEFT) )
        target_dir.x -= ENT_MAX_SPEED;
    
    if( ImGui::IsKeyDown(GLFW_KEY_RIGHT) )
        target_dir.x += ENT_MAX_SPEED;

    if( ImGui::IsKeyDown(GLFW_KEY_B) )
        team.action = AI_behaviour::follow_b;
    
    if( ImGui::IsKeyDown(GLFW_KEY_RIGHT_CONTROL) )
        team.action = AI_behaviour::chase_b;
    
    if( ImGui::IsKeyDown(GLFW_KEY_RIGHT_SHIFT) )
        team.action = AI_behaviour::no_b;
    
    if( ImGui::IsKeyDown(GLFW_KEY_1) )
        team.current_form = Formation::no_form;

    if( ImGui::IsKeyPressed(GLFW_KEY_2) )
        team.current_form = Formation::ring_form;

    if( ImGui::IsKeyPressed(GLFW_KEY_D) ) {
        auto& control     = context.template getSCmpByType<InterfaceControl>();
        control.showDebug = !control.showDebug;
    }

    target_dir.normalize();
    target_dir *= ENT_MAX_SPEED;

    accel  = (target_dir - dir);
    accel /= ENT_TIME_TO_TARGET;

    if(accel.length2() > ENT_MAX_ACCEL2) {
        accel.normalize();
        accel *= ENT_MAX_ACCEL;
    }

    return true;
}

}