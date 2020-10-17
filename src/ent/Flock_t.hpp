#pragma once
#include <utils/Vec2.hpp>
#include <utils/Alias.hpp>

#include <vector>
#include <array>

namespace AIP {

struct Entity_t;

struct Flock_t {
    explicit Flock_t() : flock_id(++counterID) {
        squadron.reserve(5);
        target.x = patrol_coord[patrol_index];
        target.y = patrol_coord[patrol_index+1];
    };

    Vec2<float> MC     { 0, 0 }; //Centro del conjunto.
    std::vector<Entity_t*> squadron { };

    std::array<float,8> patrol_coord { 100.f,100.f, 600.f,100.f, 600.f,600.f, 100.f,600.f };
    std::size_t         patrol_index { 0 };

    Vec2<float> target { };


private:
    inline static flockID counterID { 0 };
                  flockID flock_id  { 0 };
};

/*
    TODO:
        - darle una ruta como param u otra forma de objetivo.
        - analizar si actuará como entidad colectiva y tendrá cmps.
*/

} //NS
