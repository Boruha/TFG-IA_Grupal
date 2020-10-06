#pragma once
#include <memory>

namespace AIP {

struct Manager_t;

struct System_t {
    virtual ~System_t() = default;
    
    virtual void init() noexcept = 0;
    virtual bool update(std::unique_ptr<Manager_t>& context) noexcept = 0;
};

}