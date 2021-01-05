#include <sys/AttackSystem.hpp>

#include <ent/Entity_t.hpp>

#include <cmp/CombatComponent.hpp>

#include <iostream>

namespace AIP {

template <typename Context_t>
bool 
AttackSystem<Context_t>::update(Context_t& context, const fixed64_t DeltaTime) noexcept {

    while( !attack_msg.empty() ) {
        
        auto& last_msg = attack_msg.back();

        auto& ent        = context.getEntityByID(last_msg.eid_damaged);
        auto* combat_cmp = ent.template getComponent<CombatComponent>();
        
        combat_cmp->health -= last_msg.amount;
        std::cout << "aaaaaah me dañaste\n\n";

        if(combat_cmp->health <= 0) {
            std::cout << "aaaaaah me mataste\n\n";
            context.deleteEntity(last_msg.eid_damaged);
            attack_msg.pop_back(); //ESTO NO DEBERIA ESTAR AQUI
            return false;
        }

        attack_msg.pop_back();
    }
    return true;
}

} // NS