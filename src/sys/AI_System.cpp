#include <sys/AI_System.hpp>
#include <man/Manager_t.hpp>
#include <ent/Entity_t.hpp>
#include <cmp/AI_Component.hpp>
#include <cmp/MovementComponent.hpp>

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

    auto diff_X   = mov_cmp->coord_X - route[index];
    auto diff_Y   = mov_cmp->coord_Y - route[index + 1];
    auto distance = (diff_X * diff_X) + (diff_Y * diff_Y);

    if(arrive(distance))
        index = (index + 2)/route.size();

    seek();
}

void
AI_System::seek() noexcept { 

}

bool
AI_System::arrive(float dist2obj) noexcept {
    return dist2obj < ARRIVE_MIN_DIST2;
}

} //NS