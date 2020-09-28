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

private:
    const uint32_t window_w { 0 }, window_h { 0 }, framebuffer_size { 0 };
    std::unique_ptr<uint32_t[]> framebuffer { nullptr };
};

}
