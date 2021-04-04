#include <game/sys/AttackSystem.hpp>
#include <game/cmp/CombatComponent.hpp>
#include <game/cmp/EventCmp_t.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

template <typename Context_t>
void 
AttackSystem<Context_t>::update(Context_t& context) noexcept {
    auto& eventCmp = context.template getSCmpByType<EventCmp_t>();
    auto& atk_vec  = eventCmp.attack_msg;
    
    std::for_each(atk_vec.rbegin(), atk_vec.rend(), [&](auto& msg) {
            auto& combat_cmp   = context.template getCmpByEntityID<CombatComponent>( msg.eid_damaged );
            combat_cmp.health -= msg.amount;

            if(combat_cmp.health <= 0)
                eventCmp.death_msg.emplace(msg.eid_damaged, EntType::Human);

            atk_vec.pop_back();
    });
}

} // NS