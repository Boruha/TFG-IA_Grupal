#include <sys/AI_System.hpp>
#include <man/Manager_t.hpp>

#include <ent/Entity_t.hpp>
#include <ent/Flock_t.hpp>

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
    auto& flock_ent_vec = context->getFlocks();
    
    /*MC UPDATE*/
    auto update_flock_MC = [&](std::unique_ptr<Flock_t>& flock_ent) {
        auto& mc_coords     = flock_ent->MC;
        auto& ent_squadron  = flock_ent->squadron;

        mc_coords.x.number = mc_coords.y.number = 0u;
        
        for(auto* ent : ent_squadron) {                                 //Itera por cada integrante
            auto* mov_cmp = ent->getComponent<MovementComponent>();

            mc_coords.x += mov_cmp->coords.x;                           //suma sus coordenadas
            mc_coords.y += mov_cmp->coords.y;
        }
        mc_coords.x /= ent_squadron.size();                             //saca el promedio en cada eje.
        mc_coords.y /= ent_squadron.size();
    };


    std::for_each(begin(flock_ent_vec), end(flock_ent_vec), update_flock_MC);
    
    for(auto& flock : flock_ent_vec)
        patrol(flock);

    return true;
}

void
AI_System::patrol(std::unique_ptr<Flock_t>& flock_ent) noexcept {
    auto& ents_in_squadron = flock_ent->squadron;  //vec entity_t*
    auto& mc_coords        = flock_ent->MC;        //centro de masas flock

    patrol_target_update(flock_ent);

    auto arrive_patrol_cohesion = [&](Entity_t* entity) {
        auto* mov_cmp = entity->getComponent<MovementComponent>();

        arrive(mov_cmp, flock_ent->target, mc_coords);
        cohesion(mov_cmp, mc_coords);

        mov_cmp->separation.x.number = mov_cmp->separation.y.number = 0;
    };
    std::for_each(begin(ents_in_squadron), end(ents_in_squadron), arrive_patrol_cohesion);

    separation(ents_in_squadron);
}

void
AI_System::patrol_target_update(std::unique_ptr<Flock_t>& flock_ent) noexcept {
    const auto& mc_coords = flock_ent->MC;
          auto& target    = flock_ent->target;

    fixed_vec2 diff_flock2target { };
    diff_flock2target.x.number = target.x.number - mc_coords.x.number;
    diff_flock2target.y.number = target.y.number - mc_coords.y.number;

    if( diff_flock2target.length2() < FLOCK_ARRIVE_MIN_DIST2 ) {
        const auto& route = flock_ent->patrol_coord;
              auto& index = flock_ent->patrol_index;
                
        index    = (index + 2) % route.size();
        target.x = route[index];
        target.y = route[index+1];
    }
}

void
AI_System::cohesion(MovementComponent* mov_cmp, const ufixed_vec2& flock_mc) noexcept {
    auto& cohesion_vec = mov_cmp->cohesion; 

    cohesion_vec.x.number = flock_mc.x.number - mov_cmp->coords.x.number;
    cohesion_vec.y.number = flock_mc.y.number - mov_cmp->coords.y.number;

    if(cohesion_vec.length2() < COHESION_RAD2)
        cohesion_vec.x.number = cohesion_vec.y.number = 0;
}

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

/*Generic behaviours*/
void
AI_System::arrive(MovementComponent* mov_cmp, const ufixed_vec2& target, const ufixed_vec2& flock_mc) noexcept {
    auto& to_target    = mov_cmp->target;
    auto& my_coords    = mov_cmp->coords;
    mov_cmp->Accel_mod = 1;
    
    //Calculo posición relativa en el destino del flock.
    int32_t relative_pos_x = my_coords.x.number - flock_mc.x.number;
    int32_t relative_pos_y = my_coords.y.number - flock_mc.y.number;
    //marcamos la posicion relativa como obj.
    int32_t own_target_x   = target.x.number    + relative_pos_x;
    int32_t own_target_y   = target.y.number    + relative_pos_y;

    to_target.x.number = own_target_x - my_coords.x.number;
    to_target.y.number = own_target_y - my_coords.y.number;

    auto dist_to_target = to_target.length2(); 

    if(dist_to_target < ENT_DECELERATE_MIN_DIST2)
        mov_cmp->Accel_mod = -1;

    if(dist_to_target < ENT_ARRIVE_MIN_DIST2) {
        std::cout << "LLEGO\n";
        to_target.x.number = to_target.y.number = 0;
    }
}

} //NS


//std::cout << "Vec target:     " << mov_cmp->target.x << " - " << mov_cmp->target.y << "\n";
//std::cout << "Vec cohesion:   " << mov_cmp->cohesion.x << " - " << mov_cmp->cohesion.y << "\n";
//std::cout << "Vec separation: " << mov_cmp->separation.x << " - " << mov_cmp->separation.y << "\n";
