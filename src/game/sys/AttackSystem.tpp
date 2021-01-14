#include <game/sys/AttackSystem.hpp>
#include <game/cmp/CombatComponent.hpp>

#include <ecs/ent/Entity_t.hpp>

namespace AIP {

template <typename Context_t>
bool 
AttackSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {

    while( !attack_msg.empty() ) {
        
        auto& last_msg   = attack_msg.back();
        auto& combat_cmp = context.template getCmpByEntityID<CombatComponent>( last_msg.eid_damaged );
        
        combat_cmp.health -= last_msg.amount;

        if(combat_cmp.health <= 0) {
            context.deleteEntity(last_msg.eid_damaged);
            attack_msg.pop_back(); //ESTO NO DEBERIA ESTAR AQUI
            return false;
        }

        attack_msg.pop_back();
    }
    return true;
}

} // NS