#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <X11/X.h>
#include <X11/keysym.h>

namespace AIP {

struct InputComponent : BECS::Component_t {
    explicit InputComponent(const BECS::entID eid) : Component_t(eid) { }

    //Si queremos distintos mapeos tocará ampliar la herencia o crear tipos de cmps "independientes entre ellos".
    KeySym key_Up    { XK_Up    };
    KeySym key_Down  { XK_Down  };
    KeySym key_Left  { XK_Left  };
    KeySym key_Right { XK_Right };

};

} //NS