#include <game/sys/CooldownSystem.hpp>
#include <game/cmp/CombatComponent.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

template <typename Context_t>
void 
CooldownSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& combatCmps = context.template getComponentVector<CombatComponent>();

    std::for_each(begin(combatCmps), end(combatCmps), [&DeltaTime](CombatComponent& combat) {
        if(combat.current_attack_cd > 0)
            combat.current_attack_cd -= DeltaTime;
    });

    auto& bb = context.template getSCmpByType<BlackBoardCmp>();
    if(bb.current_reaction_cd.number > 0)
            bb.current_reaction_cd -= DeltaTime;
}

} // NS