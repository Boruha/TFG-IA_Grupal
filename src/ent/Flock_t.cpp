#include <ent/Flock_t.hpp>
#include <utility>

namespace AIP {

Flock_t::Flock_t() : flock_id(++counterID) {
    squadron.reserve(5);
    target_list.reserve(4);
    target_list = { ufixed_vec2(600u, 100u), ufixed_vec2(600u, 600u)
                  , ufixed_vec2(100u, 600u), ufixed_vec2(100u, 100u) };
    
    current_target = target_list.at(target_index);
}

Flock_t::~Flock_t() { 
    squadron.clear(); 
    target_list.clear();
}

void 
Flock_t::setTarget(std::vector<ufixed_vec2>& new_target_list) {
    target_list    = std::vector(std::move(new_target_list));
    target_index   = 0u;
    current_target = target_list.at(target_index);
}

void 
Flock_t::setTarget(ufixed_vec2& new_target) {
    target_list.clear();
    target_list.push_back(std::move(new_target));
    target_index   = 0u;
    current_target = target_list.at(target_index);
}

} //NS