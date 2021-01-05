#pragma once
#include <sys/System_t.hpp>

#include <utils/Keyboard_t.hpp>

namespace AIP {

template <typename Context_t>
struct InputSystem : System_t {
    explicit InputSystem();
    bool     update(Context_t& context, const fixed64_t DeltaTime) noexcept;

private:
    static void onkeypress(KeySym key);
    static void onkeyrelease(KeySym key);

    inline static Keyboard_t keyboard { };
};


}