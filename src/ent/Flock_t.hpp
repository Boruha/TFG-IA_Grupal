#pragma once
#include <utils/Vec2.hpp>
#include <utils/Alias.hpp>
#include <utils/ufixed32_t.hpp>


#include <vector>
#include <array>

namespace AIP {

struct Entity_t;

enum class Flock_behaviour : uint16_t {
    no_b     = 0u,
    patrol_b = 1u,
    arrive_b  = 2u,
    flee_b   = 3u,
    pursue_b = 4u,
    evade_b  = 5u
};

struct Flock_t {
    explicit Flock_t();
    ~Flock_t();
    
    void setTarget(std::vector<ufixed_vec2>& new_target_list);
    void setTarget(ufixed_vec2& new_target);

    ufixed_vec2 current_target { 0u, 0u };
    ufixed_vec2 MC             { 0u, 0u }; //Centro del conjunto.
    std::size_t target_index   { 0u };

    std::vector<ufixed_vec2> target_list { };
    std::vector<Entity_t*>   squadron     { };

    Flock_behaviour current_behaviour { Flock_behaviour::patrol_b };

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
