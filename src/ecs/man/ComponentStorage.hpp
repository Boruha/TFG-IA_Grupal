#pragma once
#include <ecs/cmp/CmpVector_t.tpp>

#include <unordered_map>
#include <memory>
#include <optional>
#include <functional>

namespace BECS {

struct ComponentStorage {
    template <typename ref>
    using opt_refw = std::optional< std::reference_wrapper<ref> >;
    
      explicit ComponentStorage()                         = default;
             
               ComponentStorage(const ComponentStorage& ) = delete;
               ComponentStorage(const ComponentStorage&&) = delete;
    ComponentStorage& operator=(const ComponentStorage& ) = delete;
    ComponentStorage& operator=(const ComponentStorage&&) = delete;

    template<typename T>               constexpr       T&              createComponent(const T& new_cmp) noexcept;

    template<typename T> [[nodiscard]] constexpr       std::vector<T>& getCmpCollection()                noexcept;
    //template<typename T> [[nodiscard]] constexpr const std::vector<T>& getCmpCollection() const          noexcept;

    template<typename T> [[nodiscard]] constexpr       T&              getCmpByEntityID(const entID eid) noexcept;
    //template<typename T> [[nodiscard]] constexpr const T&              getCmpByEntityID(const entID eid) const noexcept;

    bool deleteCmpByTypeIDAndEntityID(cmpTypeID cid, entID eid) noexcept;

private:
    std::unordered_map<std::size_t , std::unique_ptr<CmpCollection>> cmp_map;
};

}