#pragma once

#include <cmp/Component_t.hpp>
#include <utils/Vec2.hpp>

namespace AIP {

struct MovementComponent : Component_t {
  explicit MovementComponent(const entID entityID, const fixed64_t c_X, const fixed64_t c_Y) 
    : Component_t(entityID), coords(c_X, c_Y) { }

  fixed_vec2 coords { 0, 0 };
  fixed_vec2 dir    { 0, 0 }; //desplazamiento final de la entidad
  fixed_vec2 accel_to_target  { 0, 0 }; //acceleracion calculada en cada iteracion.
  fixed_vec2 cohesion_force   { 0, 0 }; //si hay elementos cercanos, fuerza que los agrupa.
  fixed_vec2 separation_force { 0, 0 }; //si hay elementos cercanos, fuerza que los separa.

  //componentes aux
  fixed_vec2 sep_copy_to_draw { 0, 0 };
  fixed_vec2 coh_copy_to_draw { 0, 0 };
  fixed64_t  cohesion_count   { 0l };
};

}