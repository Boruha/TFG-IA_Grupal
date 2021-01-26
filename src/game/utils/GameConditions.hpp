#pragma once
#include <cstdint>

enum class GameConditions : int16_t {
    Loop     = 0u,
    Cerrar   = 1u,
    Derrota  = 2u,
    Victoria = 3u
};