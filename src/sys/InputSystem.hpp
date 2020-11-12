#pragma once
#include <sys/System_t.hpp>

#include <utils/Keyboard_t.hpp>

namespace AIP {

struct Manager_t;

struct InputSystem : System_t {
    explicit InputSystem();

    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const fixed32_t DeltaTime) noexcept override;

private:
    static void onkeypress(KeySym key);
    static void onkeyrelease(KeySym key);

    inline static Keyboard_t keyboard { };
};


}