#include <game/sys/InputSystem.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/AI_Component.hpp>
#include <game/cmp/TeamComponent.hpp>
#include <game/utils/AI_Constants.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <engineGL/EngineManager.hpp>


namespace AIP {

template <typename Context_t>
bool 
InputSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto  pj_id = context.template getPlayerID();
    auto& mov   = context.template getCmpByEntityID<MovementComponent>( pj_id );
    auto& dir   = mov.dir;
    auto& accel = mov.accel_to_target;

    fvec2<fint_t<int64_t>> target_dir { };

    if( ImGui::IsKeyDown(GLFW_KEY_UP) )
        target_dir.y -= ENT_MAX_SPEED;
    
    if( ImGui::IsKeyDown(GLFW_KEY_DOWN) )
        target_dir.y += ENT_MAX_SPEED;
    
    if( ImGui::IsKeyDown(GLFW_KEY_LEFT) )
        target_dir.x -= ENT_MAX_SPEED;
    
    if( ImGui::IsKeyDown(GLFW_KEY_RIGHT) )
        target_dir.x += ENT_MAX_SPEED;

    if( ImGui::IsKeyDown(GLFW_KEY_B) )
        comand_msg.emplace(AI_behaviour::follow_b);

    if( ImGui::IsKeyDown(GLFW_KEY_SPACE) )
        comand_msg.emplace(AI_behaviour::chase_b);
    
    if( ImGui::IsKeyDown(GLFW_KEY_1) ) {
        auto& team_cmp        = context.template getCmpByEntityID<TeamComponent>( pj_id );
        team_cmp.current_form = Formation::no_form;
    }

    if( ImGui::IsKeyPressed(GLFW_KEY_2) ) {
        auto& team_cmp        = context.template getCmpByEntityID<TeamComponent>( pj_id );
        team_cmp.current_form = Formation::follow_form;
    }

    if( ImGui::IsKeyPressed(GLFW_KEY_3) ) {
        auto& team_cmp        = context.template getCmpByEntityID<TeamComponent>( pj_id );
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

    return true;
}

}