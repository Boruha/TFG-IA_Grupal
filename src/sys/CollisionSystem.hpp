#pragma once
#include <sys/System_t.hpp>

#include <memory>

namespace AIP {

struct Manager_t;

struct CollisionSystem : System_t {
    explicit CollisionSystem() = default;

    void init() noexcept override;
    bool update(std::unique_ptr<Manager_t>& context) noexcept override;
};

} // NS
