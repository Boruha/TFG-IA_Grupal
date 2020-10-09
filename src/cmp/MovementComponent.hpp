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
  explicit MovementComponent(const entID entityID, const float c_X, const float c_Y) 
    : Component_t(entityID), coords(c_X, c_Y) { }

  Vec2<float> coords { 0.f, 0.f };
  Vec2<float> dir    { 0.f, 0.f }; //currently facing
  //limitar la cantidad de:
  // - grados que puede rotar la AI  (posibles const)
  // - variación de la velocidad

  //Posible tener una velocidad normal (andar xd) y un cap de sprint + acceleración.
};

}