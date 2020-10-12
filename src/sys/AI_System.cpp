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


    /*CALCULO CM*/
    auto update_flock_MC = [&](std::unique_ptr<Flock_t>& flock_ent) { //crear operadores de suma, resta y div para Vec<T>
        auto& mc_coords     = flock_ent->MC;
        auto& ent_squadron  = flock_ent->squadron;

        mc_coords.x = mc_coords.y = 0.f;
        
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
    auto& ent_squadron = flock_ent->squadron;  //vec entity_t*
    auto& mc_coords    = flock_ent->MC;        //centro flock

    const auto& route = flock_ent->patrol_coord;   //puntos patrulla
          auto& index = flock_ent->patrol_index;   //objetivo actual

    Vec2<float> diff_flock2target { route[index] - mc_coords.x, route[index+1] - mc_coords.y };

    if(arrive( diff_flock2target.length() )) {                     //Si el centro del flock ya llegó cambia de objetivo
        index  = (index + 2) % route.size();                       //y recalcula la dirección del flock.
        diff_flock2target.x = route[index]   - mc_coords.x;
        diff_flock2target.y = route[index+1] - mc_coords.y;
    }

    /*Seek + Cohesion*/
    auto seek_patrol_cohesion = [&](Entity_t* entity) {
        auto* mov_cmp = entity->getComponent<MovementComponent>();
        //Seek
        mov_cmp->target.x  = diff_flock2target.x;
        mov_cmp->target.y  = diff_flock2target.y;
        //Cohesion
        mov_cmp->cohesion.x = mc_coords.x - mov_cmp->coords.x;
        mov_cmp->cohesion.y = mc_coords.y - mov_cmp->coords.y;

        mov_cmp->separation.x = 0.f;
        mov_cmp->separation.y = 0.f;
    };

    std::for_each(begin(ent_squadron), end(ent_squadron), seek_patrol_cohesion);

    /*Separation*/
    for(auto it_current_ent = begin(ent_squadron); it_current_ent < end(ent_squadron); ++it_current_ent ) {
        auto* mov_cmp_current = (*it_current_ent)->getComponent<MovementComponent>();

        for(auto it_comp_ent = it_current_ent + 1; it_comp_ent != end(ent_squadron); ++it_comp_ent ) {
            auto* mov_cmp_comp = (*it_comp_ent)->getComponent<MovementComponent>();
            
            Vec2<float> ent_separation { mov_cmp_current->coords.x - mov_cmp_comp->coords.x,
                                         mov_cmp_current->coords.y - mov_cmp_comp->coords.y };
            
            auto dist = ent_separation.length();

            if(dist < SEPARATION_RAD) {
                float strength = std::min(10000/(dist*dist), SEEK_MAX_SPEED);
                ent_separation.normalize();

                mov_cmp_current->separation.x += strength * ent_separation.x;
                mov_cmp_current->separation.y += strength * ent_separation.y;

                mov_cmp_comp->separation.x += strength * (ent_separation.x * -1);
                mov_cmp_comp->separation.y += strength * (ent_separation.y * -1);
            } //end_if
        } //end_for2
    } //end_for1

    /*Result*/
    for(auto* ent : ent_squadron) {
        auto* mov_cmp = ent->getComponent<MovementComponent>();

        mov_cmp->dir.x = mov_cmp->target.x + mov_cmp->cohesion.x + mov_cmp->separation.x;
        mov_cmp->dir.y = mov_cmp->target.y + mov_cmp->cohesion.y + mov_cmp->separation.y;
        mov_cmp->dir.normalize();
    }
}

bool
AI_System::arrive(float dist2obj) noexcept {
    return dist2obj < ARRIVE_MIN_DIST2;
}


} //NS