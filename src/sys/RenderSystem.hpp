#pragma once
#include <cstdint>
#include <memory>

#include <sys/System.hpp>

namespace AIP {

struct RenderSystem : System {
    explicit RenderSystem(const uint32_t w, const uint32_t h);
            ~RenderSystem() override;

    void init()   override;
    bool update() override;

    static constexpr uint32_t Red    = 0x00FF0000;
    static constexpr uint32_t Green  = 0x0000FF00;
    static constexpr uint32_t Blue   = 0x000000FF;
    static constexpr uint32_t White  = 0x00FFFFFF;
    static constexpr uint32_t Black  = 0x00000000;

private:
    const uint32_t window_w { 0 }, window_h { 0 }, framebuffer_size { 0 };
    std::unique_ptr<uint32_t[]> framebuffer { nullptr };
};

}
