#pragma once
#include <vector>
#include <memory>

namespace AIP {

struct Entity_t;

struct Manager_t {
    virtual ~Manager_t() = default;

    virtual const std::vector<std::unique_ptr<Entity_t>>&  getEntities() const = 0;     
};

}
