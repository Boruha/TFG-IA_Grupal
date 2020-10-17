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
    auto& ents_in_squadron = flock_ent->squadron;  //vec entity_t*
    auto& mc_coords        = flock_ent->MC;        //centro de masas flock

    patrol_target_update(flock_ent);

    auto arrive_patrol_cohesion = [&](Entity_t* entity) {
        auto* mov_cmp = entity->getComponent<MovementComponent>();

        arrive(mov_cmp, flock_ent->target);
        cohesion(mov_cmp, mc_coords);

        mov_cmp->separation.x = mov_cmp->separation.y = 0.f; //FEO "-.- (pasar reset al sistema)
    };
    std::for_each(begin(ents_in_squadron), end(ents_in_squadron), arrive_patrol_cohesion);

    separation(ents_in_squadron);

    /*Result*/                                  //FEOOOOOO T.T (pasar nomalizacion al sistema)
    for(auto* ent : ents_in_squadron) {
        auto* mov_cmp = ent->getComponent<MovementComponent>();

        mov_cmp->dir.x = mov_cmp->target.x + mov_cmp->cohesion.x + mov_cmp->separation.x;
        mov_cmp->dir.y = mov_cmp->target.y + mov_cmp->cohesion.y + mov_cmp->separation.y;
        mov_cmp->dir.normalize();
    }
}

void
AI_System::patrol_target_update(std::unique_ptr<Flock_t>& flock_ent) noexcept {
    const auto& mc_coords = flock_ent->MC;
          auto& target    = flock_ent->target;

    Vec2<float> diff_flock2target { target.x - mc_coords.x, target.y - mc_coords.y };

    if( diff_flock2target.length2() < FLOCK_ARRIVE_MIN_DIST2 ) {
        const auto& route = flock_ent->patrol_coord;
              auto& index = flock_ent->patrol_index;
                
        index    = (index + 2) % route.size();
        target.x = route[index];
        target.y = route[index+1];
    }
}

void
AI_System::cohesion(MovementComponent* mov_cmp, const Vec2<float>& flock_mc) noexcept {
    auto& cohesion_vec = mov_cmp->cohesion; 

    cohesion_vec.x = flock_mc.x - mov_cmp->coords.x;
    cohesion_vec.y = flock_mc.y - mov_cmp->coords.y;

    if(cohesion_vec.length2() < COHESION_RAD2)
        cohesion_vec.x = cohesion_vec.y = 0.f;
}

void
AI_System::separation(std::vector<Entity_t*>& squadron) noexcept {
    for(auto it_current_ent = begin(squadron); it_current_ent < end(squadron); ++it_current_ent ) {
        auto* mov_cmp_current = (*it_current_ent)->getComponent<MovementComponent>();

        for(auto it_comp_ent = it_current_ent + 1; it_comp_ent != end(squadron); ++it_comp_ent ) {
            auto* mov_cmp_comp = (*it_comp_ent)->getComponent<MovementComponent>();
            
            Vec2<float> ent_separation { mov_cmp_current->coords.x - mov_cmp_comp->coords.x,
                                         mov_cmp_current->coords.y - mov_cmp_comp->coords.y };
            
            auto dist = ent_separation.length2();

            if(dist < SEPARATION_RAD2) {
                float strength = std::min(SEPARATION_NUM/dist, ENT_MAX_SPEED);
                ent_separation.normalize();

                mov_cmp_current->separation.x += strength * ent_separation.x;
                mov_cmp_current->separation.y += strength * ent_separation.y;

                mov_cmp_comp->separation.x += strength * (ent_separation.x * -1);
                mov_cmp_comp->separation.y += strength * (ent_separation.y * -1);
            } //end_if

        } //end_for2
    } //end_for1
}

/*Generic behaviours*/
void
AI_System::arrive(MovementComponent* mov_cmp, const Vec2<float>& target) noexcept {
    auto& to_target = mov_cmp->target;

    to_target.x = target.x - mov_cmp->coords.x;
    to_target.y = target.y - mov_cmp->coords.y;

    if(to_target.length2() < ENT_ARRIVE_MIN_DIST2)
        to_target.x = to_target.y = 0.f;
}

} //NS


//std::cout << "Vec target:     " << mov_cmp->target.x << " - " << mov_cmp->target.y << "\n";
//std::cout << "Vec cohesion:   " << mov_cmp->cohesion.x << " - " << mov_cmp->cohesion.y << "\n";
//std::cout << "Vec separation: " << mov_cmp->separation.x << " - " << mov_cmp->separation.y << "\n";
