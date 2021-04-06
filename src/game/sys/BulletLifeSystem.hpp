#pragma once

namespace AIP {

template <typename Context_t>
struct BulletLifeSystem {
    void update(Context_t& context) noexcept;

private:
    void spawnBullets(Context_t& context) noexcept;
};

} // NS