#pragma once
#include <utils/Vec2.hpp>
#include <utils/Alias.hpp>
#include <utils/ufixed32_t.hpp>


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

    ufixed_vec2 MC { 0u, 0u }; //Centro del conjunto.
    std::vector<Entity_t*> squadron { };

    std::array<ufixed32_t,8> patrol_coord { 100u,100u, 600u,100u, 600u,600u, 100u,600u };
    std::size_t              patrol_index { 0u };

    ufixed_vec2 target { 0u, 0u };


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
