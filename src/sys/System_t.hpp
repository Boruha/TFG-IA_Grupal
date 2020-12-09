#pragma once
#include <utils/ufixed64_t.hpp>
#include <utils/Message.hpp>

#include <memory>
#include <vector>

namespace AIP {

struct Manager_t;

struct System_t {
    virtual ~System_t() = default;
    
    virtual void init() noexcept = 0;
    virtual bool update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept = 0;

    inline static std::vector<FPS_Message> fps_msg; 
};

}