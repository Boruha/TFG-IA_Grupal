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
AI_System::update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept {
    auto& ai_cmp_vec = context->getAI_Cmps();
    
    /*MC UPDATE*/
    auto update_ai_movement = [&](std::unique_ptr<AI_Component>& ai_cmp) {
        auto& ent     = context->getEntityByID( ai_cmp->getEntityID() );
        auto* mov_cmp = ent->getComponent<MovementComponent>();

        updateTarget(ai_cmp, mov_cmp);
        arrive(mov_cmp, ai_cmp->target_vec.at(ai_cmp->target_index) );
    };

    std::for_each(begin(ai_cmp_vec), end(ai_cmp_vec), update_ai_movement);

    return true;
}

/* BASIC BEHAVIOURS FUCTIONS */
void
AI_System::arrive(MovementComponent* mov_cmp, const fixed_vec2& target) noexcept {
    auto& to_target    = mov_cmp->dir;
    auto& my_coords    = mov_cmp->coords;

    to_target.x = target.x - my_coords.x;
    to_target.y = target.y - my_coords.y;

    auto dist_to_target = to_target.length2(); 

    if(dist_to_target < ENT_ARRIVE_MIN_DIST2)
        to_target.x.number = to_target.y.number = 0;

    to_target.normalize();
}

/* AUX FUCTIONS */
void 
AI_System::updateTarget(std::unique_ptr<AI_Component>& ai_cmp, MovementComponent* mov_cmp) noexcept {
    auto& coords = mov_cmp->coords;
    auto& route  = ai_cmp->target_vec;
    auto& index  = ai_cmp->target_index;
    auto& target = route.at(index);

    fixed_vec2 diff_2target { };
    diff_2target.x = target.x - coords.x;
    diff_2target.y = target.y - coords.y;

    if( diff_2target.length2() < ENT_ARRIVE_MIN_DIST2 ) {        
        index  = (index + 1) % route.size();
        target = route.at(index);
    }
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