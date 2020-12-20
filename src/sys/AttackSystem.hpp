#pragma once
#include <sys/System_t.hpp>

#include <memory>

namespace AIP {

struct Manager_t;

struct AttackSystem : System_t {
    explicit AttackSystem() = default;

    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept override;
};

} // NS