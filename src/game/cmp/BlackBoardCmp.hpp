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
#include <game/utils/fvec2.hpp>

#include <vector>

namespace AIP {

struct BlackBoardCmp{
    fint_t<int64_t> reaction_cd         { 0.2f }; //tiempo entre reacciones.
    fint_t<int64_t> current_reaction_cd { 0l   }; //tiempo hasta poder reaccionar de nuevo.
    fvec2<fint_t<int64_t>> player_pos   {  };
    fvec2<fint_t<int64_t>> player_dir   {  };
};

} //NS