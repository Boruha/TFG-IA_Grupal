#pragma once
#include <cstdint>

struct Entity_t
{
public:
    explicit Entity_t() : entID(++counterID) { }
            ~Entity_t() = default;

    const int16_t getID() const { return entID; }
    

private:
    inline static int16_t counterID { 0 };
    const         int16_t entID     { 0 };

};
