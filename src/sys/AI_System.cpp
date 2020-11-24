#include <sys/AI_System.hpp>
#include <man/Manager_t.hpp>

#include <ent/Entity_t.hpp>

#include <cmp/AI_Component.hpp>
#include <cmp/MovementComponent.hpp>

#include <utils/AI_Constants.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

void
AI_System::init() noexcept { }

bool
AI_System::update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept {
    auto& ai_cmp_vec = context->getAI_Cmps();
    
    /*MC UPDATE*/
    auto update_ai_movement = [&](std::unique_ptr<AI_Component>& ai_cmp) {
        auto& ent     = context->getEntityByID( ai_cmp->getEntityID() );
        auto* mov_cmp = ent->getComponent<MovementComponent>();

        arrive(mov_cmp, ai_cmp);
    };

    std::for_each(begin(ai_cmp_vec), end(ai_cmp_vec), update_ai_movement);

    return true;
}

/* BASIC BEHAVIOURS FUCTIONS */
void
AI_System::arrive(MovementComponent* mov_cmp, std::unique_ptr<AI_Component>& ai_cmp) noexcept {
    auto& my_coords = mov_cmp->coords;
    auto& my_accel  = mov_cmp->accel;
    auto& my_direct = mov_cmp->dir;

    auto  target_dir = ai_cmp->target_vec.at(ai_cmp->target_index) - my_coords;
    auto  distance2  = target_dir.length2();
    fixed64_t target_speed { };

    //si hemos llegado miramos si hay un "target siguiente", sino nos quedamos quietos y salimos.
    if(distance2 < ENT_ARRIVE_DIST2) {
        if(auto new_target = updateTarget(ai_cmp)) {
            target_dir = (*new_target).get() - my_coords;
            distance2  = target_dir.length2();
        }
        else {
            my_accel.x.number  = my_accel.y.number  = 0;
            my_direct.x.number = my_direct.y.number = 0;
            return;
        }
    }
    //si esta lejos intenta alcanzar max speed, sino interpola [max_speed, 0]
    if(distance2 > ENT_SLOW_DIST2)
        target_speed = ENT_MAX_SPEED;
    else
        target_speed = ENT_MAX_SPEED * ( fixed64_t(target_dir.length()) / ENT_SLOW_DIST );
    
    //calculamos la aceleracion objetivo como la diferencia de  (deseada - actual) 
    target_dir.normalize();
    target_dir *= target_speed;

    my_accel  = target_dir - my_direct;
    my_accel /= ENT_TIME_TO_TARGET;

    //ajustamos la aceleracion para que no sea muy alta.
    if(my_accel.length2() > ENT_MAX_ACCEL2) {
        my_accel.normalize();
        my_accel *= ENT_MAX_ACCEL;
    }
}

/* AUX FUCTIONS */
AI_System::optVec2_refw 
AI_System::updateTarget(std::unique_ptr<AI_Component>& ai_cmp) noexcept {
    auto& route  = ai_cmp->target_vec;
    auto& index  = ai_cmp->target_index;

    auto index_fwd = (index+1) % route.size();

    if(index_fwd != index) {
        index = index_fwd;
        return std::ref(route.at(index));
    }
    return { };
}



} //NS


//std::cout << "Vec target:     " << mov_cmp->target.x << " - " << mov_cmp->target.y << "\n";
//std::cout << "Vec cohesion:   " << mov_cmp->cohesion.x << " - " << mov_cmp->cohesion.y << "\n";
//std::cout << "Vec separation: " << mov_cmp->separation.x << " - " << mov_cmp->separation.y << "\n";

/*
void
AI_System::separation(std::vector<Entity_t*>& squadron) noexcept {
    for(auto it_current_ent = begin(squadron); it_current_ent < end(squadron); ++it_current_ent ) {
        auto* mov_cmp_current = (*it_current_ent)->getComponent<MovementComponent>();

        for(auto it_comp_ent = it_current_ent + 1; it_comp_ent != end(squadron); ++it_comp_ent ) {
            auto* mov_cmp_comp = (*it_comp_ent)->getComponent<MovementComponent>();
            fixed_vec2 ent_separation { }; 
            
            ent_separation.x.number = mov_cmp_current->coords.x.number - mov_cmp_comp->coords.x.number;
            ent_separation.y.number = mov_cmp_current->coords.y.number - mov_cmp_comp->coords.y.number;
            
            auto dist { ent_separation.length2() };

            if(dist < SEPARATION_RAD2) {
                auto strength { std::min(SEPARATION_NUM/dist, ENT_MAX_SPEED) };
                ent_separation.normalize();

                auto str_result_X { strength * ent_separation.x };
                auto str_result_Y { strength * ent_separation.y };

                mov_cmp_current->separation.x += str_result_X;
                mov_cmp_current->separation.y += str_result_Y;

                mov_cmp_comp->separation.x += str_result_X * -1;
                mov_cmp_comp->separation.y += str_result_Y * -1;
            } //end_if
        } //end_for2
        
        mov_cmp_current->dir.x = mov_cmp_current->target.x + mov_cmp_current->cohesion.x + mov_cmp_current->separation.x;
        mov_cmp_current->dir.y = mov_cmp_current->target.y + mov_cmp_current->cohesion.y + mov_cmp_current->separation.y;
    } //end_for1
}
*/