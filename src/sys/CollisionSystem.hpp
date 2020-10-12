#pragma once
#include <sys/System_t.hpp>

#include <memory>

namespace AIP {

struct Manager_t;

struct CollisionSystem : System_t {
    explicit CollisionSystem() = default;

    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept override;
};

} // NS