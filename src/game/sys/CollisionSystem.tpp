#include <game/sys/CollisionSystem.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/RenderComponent.hpp>
#include <game/utils/ScreenData.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <algorithm>

namespace AIP {

template <typename Context_t>
void
CollisionSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& mov_cmp_vec = context.template getComponentVector<MovementComponent>();

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), 
        [&](MovementComponent& mov_cmp) {
                auto& ren_cmp   = context.template getCmpByEntityID<RenderComponent>( mov_cmp.getEntityID() );

                        auto& coord = mov_cmp.coords;
                const fint_t size_W { static_cast<int64_t>( ren_cmp.sprite.x ) };
                const fint_t size_H { static_cast<int64_t>( ren_cmp.sprite.y ) };

                //eje X
                if( coord.x + size_W > F_H_WINDOW_W )
                        coord.x = F_H_WINDOW_W_N + size_W;

                if( coord.x - size_W < F_H_WINDOW_W_N )
                        coord.x = F_H_WINDOW_W - size_W;

                //eje Y
                if( coord.y + size_H > F_H_WINDOW_H )
                        coord.y = F_H_WINDOW_H_N + size_H;

                if( coord.y - size_H < F_H_WINDOW_H_N )
                        coord.y = F_H_WINDOW_H - size_H;
    });

}

} //NS