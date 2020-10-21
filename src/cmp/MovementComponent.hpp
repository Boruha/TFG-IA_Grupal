#pragma once
#include <cmp/Component_t.hpp>
#include <utils/Vec2.hpp>

namespace AIP {

/*
Replantear el cmp:
  OPCS:
    1: ser solo una posición.
    2: incluir la aceleracion linear y dir(full kinematic). 
*/

struct MovementComponent : Component_t {
  explicit MovementComponent(const entID entityID, const ufixed32_t c_X, const ufixed32_t c_Y) 
    : Component_t(entityID), coords(c_X, c_Y) { }

  ufixed_vec2 coords { 0u, 0u };
  fixed_vec2  dir    { 0,  0  }; //currently facing
  
  /*flocking mov*/
  fixed_vec2  target      { 0, 0 }; 
  fixed_vec2  cohesion    { 0, 0 }; 
  fixed_vec2  separation  { 0, 0 }; 


  //limitar la cantidad de:
  // - grados que puede rotar la AI  (posibles const)
  // - variación de la velocidad

  //Posible tener una velocidad normal (andar xd) y un cap de sprint + acceleración.
};

}