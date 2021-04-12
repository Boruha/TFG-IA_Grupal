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