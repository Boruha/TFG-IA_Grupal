#pragma once
#include <cmp/Component_t.hpp>

namespace AIP {

/*
Replantear el cmp:
  OPCS:
    1: ser solo una posición.
    2: incluir la aceleracion linear y dir(full kinematic). 
*/

struct MovementComponent : Component_t {
    explicit MovementComponent(const entID entityID, const float c_X, const float c_Y) 
      : Component_t(entityID), coord_X(c_X), coord_Y(c_Y) { }

          float coord_X  {  0    };    //Esquina superior izq del dibu;
          float coord_Y  {  0    };  
    const float vel      { 200.f };    //Velocidad máxima a la que nos moveremos (Seguramente acabe fuera del cmp)
          float dir[2]   { 0, 0  };    //Indica sentido y dirección del movimiento de forma vectorial.
                                        //En un futuro próximo será de tipo vec2<T>();
};

}