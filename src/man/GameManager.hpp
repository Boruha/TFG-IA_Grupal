#pragma once
#include <man/Manager_t.hpp>
#include <vector>
#include <memory>

#include <sys/RenderSystem.hpp>

namespace AIP {

struct Entity_t;

struct GameManager : Manager_t {
    explicit GameManager();
            ~GameManager() override;

    const std::vector<std::unique_ptr<Entity_t>>&  getEntities() const override;

    bool update();

private:
    std::vector<std::unique_ptr<System_t>> systems;
    std::unique_ptr<Manager_t> manager;
};

}
