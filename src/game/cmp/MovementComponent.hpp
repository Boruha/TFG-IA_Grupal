#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/fvec2.hpp>

namespace AIP {

struct MovementComponent : BECS::Component_t {
  explicit MovementComponent(const BECS::entID entityID, const fint_t<int64_t>& c_X, const fint_t<int64_t>& c_Y) 
    : Component_t(entityID), coords(c_X, c_Y) { }

  fvec2<fint_t<int64_t>> coords           { fint_t<int64_t> { 0l }, fint_t<int64_t> { 0l } };
  fvec2<fint_t<int64_t>> dir              { fint_t<int64_t> { 0l }, fint_t<int64_t> { 0l } }; //desplazamiento final de la entidad
  fvec2<fint_t<int64_t>> accel_to_target  { fint_t<int64_t> { 0l }, fint_t<int64_t> { 0l } }; //acceleracion calculada en cada iteracion.
  fvec2<fint_t<int64_t>> cohesion_force   { fint_t<int64_t> { 0l }, fint_t<int64_t> { 0l } }; //si hay elementos cercanos, fuerza que los agrupa.
  fvec2<fint_t<int64_t>> separation_force { fint_t<int64_t> { 0l }, fint_t<int64_t> { 0l } }; //si hay elementos cercanos, fuerza que los separa.

  //componentes aux
  fvec2<fint_t<int64_t>> sep_copy_to_draw { fint_t<int64_t> { 0l }, fint_t<int64_t> { 0l } };
  fvec2<fint_t<int64_t>> coh_copy_to_draw { fint_t<int64_t> { 0l }, fint_t<int64_t> { 0l } };
  fint_t<int64_t>  cohesion_count   { 0l };
};

}