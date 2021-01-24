#pragma once
#include <game/utils/EventHandler.hpp>
#include <game/utils/Keyboard_t.hpp>
#include <game/utils/fvec2.hpp>

namespace AIP {

template <typename Context_t>
struct InputSystem : EventHandler {
    explicit InputSystem();
    bool     update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;

private:
    static void onkeypress(KeySym key);
    static void onkeyrelease(KeySym key);

    inline static Keyboard_t keyboard { };
};


}