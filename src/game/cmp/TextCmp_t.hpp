#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <string>

namespace AIP {

struct TextCmp_t : BECS::Component_t {
    explicit TextCmp_t(const BECS::entID entityID, std::string t)
        : Component_t(entityID), text(std::move(t)) { }
    
    std::string text { };
};

}