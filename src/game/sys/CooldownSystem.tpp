#include <game/sys/CooldownSystem.hpp>
#include <game/cmp/CombatComponent.hpp>

#include <algorithm>

namespace AIP {

template <typename Context_t>
void 
CooldownSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& comb_cmp_vec = context.template getComponentVector<CombatComponent>();

    std::for_each(begin(comb_cmp_vec), end(comb_cmp_vec), [&](CombatComponent& comb_cmp) {
        if(comb_cmp.current_attack_cd > 0)
            comb_cmp.current_attack_cd -= DeltaTime;
    });
}

} // NS