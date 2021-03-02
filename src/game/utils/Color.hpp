#pragma once
#include <cstdint>

namespace AIP {

enum class Color : uint32_t {
    Red    = 0xFFFF0000,
    Green  = 0xFF00FF00,
    Blue   = 0xFF0000FF,
    White  = 0xFFFFFFFF,
    Black  = 0xFF000000
};

} // NP