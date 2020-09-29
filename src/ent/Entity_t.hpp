#pragma once
#include <cstdint>
#include <vector>

#include <utils/Color.hpp>


namespace AIP {

struct Entity_t{
    explicit Entity_t(const uint32_t c_X, const uint32_t c_Y, const uint32_t s_W, const uint32_t s_H, const Color col);
            ~Entity_t() = default;

    const int16_t getID() const { return entID; }

          uint32_t coord_X  { 0 }; //Esquina superior izq del dibu;
          uint32_t coord_Y  { 0 };
    const uint32_t sprite_W { 0 }; //Tamaño del Sprite;
    const uint32_t sprite_H { 0 };
    const Color    sprite_C { Color::Red };  

private:
    inline static uint32_t counterID { 0 };
    const         uint32_t entID     { 0 };
};

} // NS