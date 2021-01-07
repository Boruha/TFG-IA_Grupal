#pragma once
#include <X11/X.h>
#include <X11/keysym.h>

#include <unordered_map>
#include <optional>

namespace AIP {

struct Keyboard_t {
    using OptKeyIt = std::optional<std::unordered_map<KeySym, bool>::iterator>;

    explicit Keyboard_t() = default;
            ~Keyboard_t() {  }

    Keyboard_t(const Keyboard_t&)            = delete;
    Keyboard_t(Keyboard_t&&)                 = delete;
    Keyboard_t& operator=(const Keyboard_t&) = delete;
    Keyboard_t& operator=(Keyboard_t&&)      = delete;

    bool     isKeyPressed(KeySym key)         noexcept;
    void     setValue(KeySym key, bool value) noexcept;
    OptKeyIt getKeyIterator(KeySym key)       noexcept;


private:
    std::unordered_map<KeySym, bool> keys {
          { XK_BackSpace, false }
        , { XK_Tab      , false }
        , { XK_Escape   , false }
        , { XK_Shift_L  , false }
        , { XK_Shift_R  , false }
        , { XK_Control_L, false }
        , { XK_Control_R, false }
        , { XK_a        , false }
        , { XK_b        , false }
        , { XK_c        , false }
        , { XK_d        , false }
        , { XK_e        , false }
        , { XK_f        , false }
        , { XK_g        , false }
        , { XK_h        , false }
        , { XK_i        , false }
        , { XK_j        , false }
        , { XK_k        , false }
        , { XK_l        , false }
        , { XK_m        , false }
        , { XK_n        , false }
        , { XK_o        , false }
        , { XK_p        , false }
        , { XK_q        , false }
        , { XK_r        , false }
        , { XK_s        , false }
        , { XK_t        , false }
        , { XK_u        , false }
        , { XK_v        , false }
        , { XK_w        , false }
        , { XK_x        , false }
        , { XK_y        , false }
        , { XK_z        , false }
        , { XK_0        , false }
        , { XK_1        , false }
        , { XK_2        , false }
        , { XK_3        , false }
        , { XK_4        , false }
        , { XK_5        , false }
        , { XK_6        , false }
        , { XK_7        , false }
        , { XK_8        , false }
        , { XK_9        , false }
        , { XK_Left     , false }
        , { XK_Up       , false }
        , { XK_Right    , false }
        , { XK_Down     , false }
    };
};



}
