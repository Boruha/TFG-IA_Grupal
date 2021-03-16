#pragma once

namespace AIP {

struct InterfaceControl {
    bool  showDebug { false };
    bool  changed   { false };
    float deltaTime { 60.f  };
    float deltaSize { 60.f  };
};

}