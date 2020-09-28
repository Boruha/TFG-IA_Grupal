#pragma once
#include <cstdint>
#include <vector>

namespace AIP {

struct Entity_t{
    explicit Entity_t(uint32_t c_X, uint32_t c_Y, uint32_t s_W, uint32_t s_H);
            ~Entity_t() = default;

    const int16_t getID() const { return entID; }

    uint32_t coord_X  { 0 }; //Esquina superior izq del dibu;
    uint32_t coord_Y  { 0 };
    uint32_t sprite_W { 0 }; //Tamaño del Sprite;
    uint32_t sprite_H { 0 };
    std::vector<uint32_t> sprite {   };   
private:
    inline static uint32_t counterID { 0 };
    const         uint32_t entID     { 0 };
};

} // NS