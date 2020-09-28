#pragma once

#include <cstdint>

namespace AIP {

// Si lo declaro como un scopped enum funciones como std::fill no pueden hacer implicit conversión
// es mejor quitar el scopped o hacer un static cast en el uso(?)

enum class Color : uint32_t {
    Red    = 0x00FF0000,
    Green  = 0x0000FF00,
    Blue   = 0x000000FF,
    White  = 0x00FFFFFF,
    Black  = 0x00000000
};

} // NP