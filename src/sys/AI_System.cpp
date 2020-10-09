#include <sys/AI_System.hpp>
#include <man/Manager_t.hpp>
#include <ent/Entity_t.hpp>
#include <cmp/AI_Component.hpp>
#include <cmp/MovementComponent.hpp>
#include <utils/AI_Constants.hpp>

#include <algorithm>

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

    Vec2<float> diff { route[index] - mov_cmp->coords.x, route[index+1] - mov_cmp->coords.y};

    if(arrive( diff.length() ))
        index = (index + 2) % route.size();

    seek(mov_cmp, route[index], route[index+1]);
}

void
AI_System::seek(MovementComponent* mov_cmp, const float x, const float y) noexcept { 
    mov_cmp->dir.x   = x - mov_cmp->coords.x;
    mov_cmp->dir.y   = y - mov_cmp->coords.y;

    mov_cmp->dir.normalize();
}

bool
AI_System::arrive(float dist2obj) noexcept {
    return dist2obj < ARRIVE_MIN_DIST2;
}

} //NS