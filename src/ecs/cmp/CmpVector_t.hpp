#pragma once
#include <game/cmp/CmpIncludeList.hpp>
#include <ecs/utils/Alias.hpp>

#include <vector>
#include <optional>

namespace BECS {

struct CmpCollection {
    virtual      ~CmpCollection()                        = default;
    virtual bool deleteCmpByEntityID(entID eid) noexcept = 0;
};

template<typename T>
struct CmpVector : CmpCollection {
    explicit CmpVector();
    bool     deleteCmpByEntityID(entID eid) noexcept override;
    auto     findCmpByEntityID(entID eid)   noexcept;

    const std::size_t    MAX_CMP_SIZE = 10u;
          std::vector<T> cmps;
};

}