#include <game/sys/AttackSystem.hpp>
#include <game/cmp/CombatComponent.hpp>

#include <ecs/ent/Entity_t.hpp>

namespace AIP {

template <typename Context_t>
void 
AttackSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {

    while( !attack_msg.empty() ) {
        auto& first_msg    = attack_msg.front();
        auto& combat_cmp   = context.template getCmpByEntityID<CombatComponent>( first_msg.eid_damaged );
        combat_cmp.health -= first_msg.amount;

        if(combat_cmp.health <= 0)
            death_msg.emplace(first_msg.eid_damaged);

        attack_msg.pop();
    }
}

} // NS