#pragma once
#include <cmp/Component_t.hpp>

namespace AIP {

struct MovementComponent : Component_t {
    explicit MovementComponent(const entID entityID, const uint32_t c_X, const uint32_t c_Y) 
      : Component_t(entityID), coord_X(c_X), coord_Y(c_Y) { }

          int32_t coord_X  {  0   }; //Esquina superior izq del dibu;
          int32_t coord_Y  {  0   };  
    const int32_t vel      { 10   };
          int32_t dir[2]   { -1, -1 };
};

}