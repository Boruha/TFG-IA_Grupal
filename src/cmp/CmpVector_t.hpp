#pragma once

#include <cmp/CmpIncludeList.hpp>

#include <utils/Alias.hpp>

#include <vector>
#include <optional>

namespace AIP {

struct CmpCollection {
    virtual ~CmpCollection() = default;
    virtual Component_t* deleteCmpByEntityID(entID eid) = 0;
};

template<typename T>
struct CmpVector : CmpCollection {
    explicit     CmpVector<T>();
    Component_t* deleteCmpByEntityID(entID eid) override;
    auto         getCmpByID(entID eid) noexcept;

    std::vector<T> cmps;
};

}