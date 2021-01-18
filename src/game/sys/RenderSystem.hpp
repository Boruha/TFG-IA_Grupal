#pragma once
#include <game/cmp/RenderComponent.hpp>
#include <game/utils/fvec2.hpp>
#include <game/utils/vec2.tpp>

namespace AIP {

struct MovementComponent;

template <typename Context_t>
struct RenderSystem {
    explicit RenderSystem(const uint32_t w, const uint32_t h);
            ~RenderSystem();

    void update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;

private:
    void clean() noexcept;

    vec2<uint32_t> continuous_to_screen(const fvec2<fint_t<int64_t>>& cont) noexcept;
    vec2<uint32_t> clip_2_draw(fvec2<fint_t<int64_t>> point)                noexcept;

    void draw_debug(const MovementComponent& mov_cmp, const RenderComponent& render_cmp) noexcept;
    void bresenham_line(const vec2<uint32_t>& screen_p_ini, const vec2<uint32_t>& screen_p_fin, int32_t dY, int32_t dX, const Color color) noexcept;
    
    void draw_line_X(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dY, const int32_t dX, const Color color) noexcept;
    void draw_line_Y(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dX, const int32_t dY, const Color color) noexcept;
    void draw_line_H(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color color) noexcept;    
    void draw_line_V(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color color) noexcept;

    const uint32_t              framebuffer_size { 0 };
    std::unique_ptr<uint32_t[]> framebuffer      { nullptr };
    bool                        debug_mode       { false };
};

}
