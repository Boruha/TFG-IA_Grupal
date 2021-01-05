#pragma once

#include <cmp/CmpVector_t.tpp>

#include <unordered_map>
#include <memory>

namespace AIP {

struct ComponentStorage {
    explicit ComponentStorage() = default;
             
               ComponentStorage(const ComponentStorage& ) = delete;
               ComponentStorage(const ComponentStorage&&) = delete;
    ComponentStorage& operator=(const ComponentStorage& ) = delete;
    ComponentStorage& operator=(const ComponentStorage&&) = delete;

    template<typename T> [[nodiscard]] constexpr       T&              createComponent(const T&& new_cmp) noexcept;
    template<typename T> [[nodiscard]] constexpr       std::vector<T>& getCmpCollection()                 noexcept;
    template<typename T> [[nodiscard]] constexpr const std::vector<T>& getCmpCollection() const           noexcept;

    Component_t* deleteCmpByTypeIDAndEntityID(cmpTypeID cid, entID eid);

private:
    std::unordered_map<std::size_t , std::unique_ptr<CmpCollection>> cmp_map;
};

}