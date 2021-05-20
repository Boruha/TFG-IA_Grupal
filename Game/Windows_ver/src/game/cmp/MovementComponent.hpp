/*
Copyright (C) <2020-2021> Borja Pozo Wals (Tw: @Chico_Riot | GitHub: Boruha)

This file is part of 'TFG: Gestión y manejo de comportamientos grupales 
de entidades en videojuegos'.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/fvec2.hpp>

namespace AIP {

struct MovementComponent : BECS::Component_t {

  explicit MovementComponent(const BECS::entID entityID, const fint_t<int64_t> c_X, const fint_t<int64_t> c_Y) 
    : Component_t(entityID), coords(c_X, c_Y) { }

  fvec2<fint_t<int64_t>> coords           = fvec2<fint_t<int64_t>>( ( 0l ), ( 0l ) ); //posicion actual.
  fvec2<fint_t<int64_t>> orientation      = fvec2<fint_t<int64_t>>( ( 0l ), ( 0l ) ); //lugar hacia donde se mira.
  fvec2<fint_t<int64_t>> dir              = fvec2<fint_t<int64_t>>( ( 0l ), ( 0l ) );//desplazamiento final de la entidad.
  fvec2<fint_t<int64_t>> accel_to_target  = fvec2<fint_t<int64_t>>( ( 0l ), ( 0l ) ); //acceleracion hacia la posición deseada.
  fvec2<fint_t<int64_t>> cohesion_force   = fvec2<fint_t<int64_t>>( ( 0l ), ( 0l ) ); //si hay entidades cercanas, fuerza que las agrupa.
  fvec2<fint_t<int64_t>> separation_force = fvec2<fint_t<int64_t>>( ( 0l ), ( 0l ) ); //si hay entidades cercanas, fuerza que las separa.

  //aux debug mode
  fvec2<fint_t<int64_t>> acc_copy_to_draw = fvec2<fint_t<int64_t>>( ( 0l ), ( 0l ) );
  fvec2<fint_t<int64_t>> sep_copy_to_draw = fvec2<fint_t<int64_t>>( ( 0l ), ( 0l ) );
  fvec2<fint_t<int64_t>> coh_copy_to_draw = fvec2<fint_t<int64_t>>( ( 0l ), ( 0l ) );
};

}