#pragma once

#include <cmp/CmpIncludeList.hpp>

#include <utils/Alias.hpp>

#include <vector>
#include <algorithm>

namespace AIP {

struct CmpCollection {
    virtual ~CmpCollection() = default;
    virtual void deleteCmpByEntityID(entID eid) = 0;
};

template<typename T>
struct CmpVector : CmpCollection {
    explicit CmpVector<T>();
    void     deleteCmpByEntityID(entID eid) override;

    std::vector<T> cmps;
};

}