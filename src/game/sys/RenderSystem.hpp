#pragma once
#include <game/cmp/RenderComponent.hpp>
#include <game/utils/fvec2.hpp>
#include <game/utils/vec2.tpp>

#include <engineGL/EngineManager.hpp>

#include <memory>

namespace AIP {

struct MovementComponent;

template <typename Context_t>
struct RenderSystem {
    explicit RenderSystem(const uint32_t w, const uint32_t h);

    bool update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;

private:
    vec2<uint32_t> continuous_to_screen(const fvec2<fint_t<int64_t>>& cont) noexcept;
    vec2<uint32_t> clip_2_draw(fvec2<fint_t<int64_t>> point)                noexcept;

    void draw_debug(const MovementComponent& mov_cmp, const RenderComponent& render_cmp) noexcept;

    bool debug_mode { true };
    std::unique_ptr<eGL::EngineManager> engine { nullptr };
};

}
