#include <sys/AI_System.hpp>
#include <man/Manager_t.hpp>
#include <ent/Entity_t.hpp>
#include <cmp/AI_Component.hpp>
#include <cmp/MovementComponent.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>

namespace AIP {

void
AI_System::init() noexcept {    }

bool
AI_System::update(const std::unique_ptr<Manager_t>& constext, const float DeltaTime) noexcept { 
    auto& ai_cmp_vec = constext->getAI_Cmps();

    auto update_ai = [&](std::unique_ptr<AI_Component>& ai_cmp) {
        auto& ent     = constext->getEntityByID(ai_cmp->getEntityID());
        auto* mov_cmp = ent->getComponent<MovementComponent>();

        patrol(ai_cmp, mov_cmp);
    };

    std::for_each(begin(ai_cmp_vec), end(ai_cmp_vec), update_ai);
    
    return true;
}

void 
AI_System::patrol(std::unique_ptr<AI_Component>& ai_cmp, MovementComponent* mov_cmp) noexcept {
    const auto& route = ai_cmp->patrol_coord; 
          auto& index = ai_cmp->patrol_index; 

    auto diff_X   = route[index]   - mov_cmp->coord_X;
    auto diff_Y   = route[index+1] - mov_cmp->coord_Y;
    auto distance = (diff_X * diff_X) + (diff_Y * diff_Y);

    if(arrive(distance)) {
        std::cout << "ARRIVE\n";
        std::cout << index << "\n";
        index = (index + 2) % route.size();
    }

    seek(mov_cmp, route[index], route[index+1]);
}

void
AI_System::seek(MovementComponent* mov_cmp, const float x, const float y) noexcept { 
    auto diff_X   = x - mov_cmp->coord_X;
    auto diff_Y   = y - mov_cmp->coord_Y;
    auto length   = std::sqrt( (diff_X * diff_X) + (diff_Y * diff_Y) );

    mov_cmp->dir[0] = diff_X/length;
    mov_cmp->dir[1] = diff_Y/length;
}

bool
AI_System::arrive(float dist2obj) noexcept {
    return dist2obj < ARRIVE_MIN_DIST2;
}

} //NS