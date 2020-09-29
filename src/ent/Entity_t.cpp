#include <ent/Entity_t.hpp>

namespace AIP {

Entity_t::Entity_t(const uint32_t c_X, const uint32_t c_Y, const uint32_t s_W, const uint32_t s_H, const Color col) 
    : coord_X(c_X), coord_Y(c_Y), sprite_W(s_W), sprite_H(s_H), sprite_C(col), entID(++counterID) { }
    
} // namespace AIP
