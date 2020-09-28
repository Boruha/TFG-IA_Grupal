#pragma once
#include <man/Manager_t.hpp>
#include <vector>
#include <memory>

#include <sys/RenderSystem.hpp>

namespace AIP {

struct GameManager : Manager_t {
    explicit GameManager();
            ~GameManager() override;

    bool update();

private:
    std::vector<std::unique_ptr<System>> systems;
};

}
