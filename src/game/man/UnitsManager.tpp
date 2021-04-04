#include <game/man/UnitsManager.hpp>
#include <game/utils/AI_Constants.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

inline void
UnitsManager::init() noexcept {
    enemies_vec.reserve(10);
    allies_vec.reserve(10);
    ally_bullets.reserve(15);
    enem_bullets.reserve(15);

    createPlayerPointer(20, 400l, 400l, Color::Green);

    createSoldier(20,  30l,  30l, Color::Red, false);
    createArcher(20,  60l, -10l, Color::Red, false);
    createSoldier(20, -10l,  20l, Color::Red, false);
    createArcher(20, -60l,  10l, Color::Red, false);
    createSoldier(20, -20l, -40l, Color::Red, false);

    createSoldier(20,  100l,  100l, Color::Red, false);
    createArcher(20,  60l, -100l, Color::Red, false);
    createSoldier(20, -130l,  20l, Color::Red, false);
    createArcher(20, -60l,  100l, Color::Red, false);
    createSoldier(20, -200l, -200l, Color::Red, false);

    createSoldier(20, 380l, 390l, Color::Blue, true);
    createSoldier(20, 360l, 400l, Color::Blue, true);
    createArcher(20, 400l, 420l, Color::Blue, true);
    createArcher(20, 380l, 420l, Color::Blue, true);
    createArcher(20, 300l, 420l, Color::Blue, true);
    createArcher(20, 380l, 400l, Color::Blue, true);
    createArcher(20, 420l, 380l, Color::Blue, true);
    createSoldier(20, 350l, 380l, Color::Blue, true);
    createSoldier(20, 340l, 380l, Color::Blue, true);
    createSoldier(20, 410l, 380l, Color::Blue, true);
}

inline void
UnitsManager::clear() noexcept {
    ent_man.clear();
    enemies_vec.clear();
    allies_vec.clear();
    ally_bullets.clear();
    enem_bullets.clear(); 
    player_id = 0u;
}

/* CREATES & DELETE */
inline void
UnitsManager::createSoldier(const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col, bool team) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    if(team)
        allies_vec.push_back(new_ent);
    else    
        enemies_vec.push_back(new_ent);

    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }    ) );
    ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent,    size  ,  size   , col) );
    ent_man.addComponentToEntity( new_ent, Collider2DCmp(     new_ent,    size  ,  size        ) );
    ent_man.addComponentToEntity( new_ent, CombatComponent(   new_ent, MEELE_ATK_DIST, team    ) );
    ent_man.addComponentToEntity( new_ent, AI_Component(      new_ent ) );
}

inline void
UnitsManager::createArcher(const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col, bool team) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    if(team)
        allies_vec.push_back(new_ent);
    else    
        enemies_vec.push_back(new_ent);

    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }    ) );
    ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent,    size  ,  size   , col) );
    ent_man.addComponentToEntity( new_ent, Collider2DCmp(     new_ent,    size  ,  size        ) );
    ent_man.addComponentToEntity( new_ent, CombatComponent(   new_ent, RANGE_ATK_DIST, team    ) );
    ent_man.addComponentToEntity( new_ent, AI_Component(      new_ent ) );
}

inline void
UnitsManager::createPlayerPointer(const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }     ) );
    ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent,    size  ,  size   , col ) );
    ent_man.addComponentToEntity( new_ent, Collider2DCmp(     new_ent,    size  ,  size         ) );
    ent_man.addComponentToEntity( new_ent, InputComponent(    new_ent ) );
    ent_man.addComponentToEntity( new_ent, TeamComponent(     new_ent ) );

    player_id = new_ent;
}

inline void 
UnitsManager::createBullet(fvec2<fint_t<int64_t>> nDir, const int64_t pos_x, const int64_t pos_y,
                bool team, BECS::entID eid, int64_t amount) noexcept {
    
    const auto new_ent = ent_man.createEntity_t();
    constexpr auto size { 10u };

    if(team)
        ally_bullets.push_back(new_ent);
    else    
        enem_bullets.push_back(new_ent);

    auto& mov = ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }               ) );
                ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent,   size   ,   size  , Color::White  ) );
                ent_man.addComponentToEntity( new_ent, Collider2DCmp(     new_ent,   size   ,   size                  ) );
                ent_man.addComponentToEntity( new_ent, BulletCmp(         new_ent, { pos_x }, { pos_y }, eid , amount ) );

    mov.dir = (nDir * (ENT_MAX_SPEED/2));
}


inline void 
UnitsManager::deleteEntity(BECS::entID eid) noexcept {
    deleteByIDFrom(allies_vec, eid);
    deleteByIDFrom(enemies_vec, eid);
}

inline void 
UnitsManager::deleteBullet(BECS::entID eid) noexcept {
    deleteByIDFrom(ally_bullets, eid);
    deleteByIDFrom(enem_bullets, eid);
}

inline void 
UnitsManager::deleteByIDFrom(std::vector<BECS::entID>& container, BECS::entID eid) noexcept {
    auto it = std::find_if(container.begin(), container.end(), 
                [&](BECS::entID id) { return id == eid; });

    if(it != container.end() ) {
        container.erase(it);
        ent_man.deleteEntity(eid);
    }
}



/* GETTERS */
template <typename SCMP_t> constexpr
SCMP_t& 
UnitsManager::getSCmpByType() noexcept {
    return std::get<SCMP_t>(singletonCmps);
}

template <typename CMP_t> constexpr
std::vector<CMP_t>&
UnitsManager::getComponentVector() noexcept {
    return ent_man.getComponentVector<CMP_t>();
}

template <typename CMP_t> constexpr
CMP_t& 
UnitsManager::getCmpByEntityID(const BECS::entID eid) noexcept {
    return ent_man.getCmpByEntityID<CMP_t>(eid);
}

inline BECS::Entity_t& 
UnitsManager::getEntityByID(BECS::entID eid) noexcept { 
    return ent_man.getEntityByID(eid);
}

inline const BECS::entID  
UnitsManager::getPlayerID() const noexcept { 
    return player_id; 
}  

inline BECS::entID  
UnitsManager::getPlayerID() noexcept { 
    return player_id; 
}

inline constexpr 
std::vector<BECS::entID>& 
UnitsManager::getEnemyIDs() noexcept {
    return enemies_vec;
} 

inline constexpr 
std::vector<BECS::entID>& 
UnitsManager::getAllyIDs() noexcept {
    return allies_vec;
}

inline constexpr 
std::vector<BECS::entID>& 
UnitsManager::getEnemBullets() noexcept {
    return enem_bullets;
}

inline constexpr 
std::vector<BECS::entID>& 
UnitsManager::getAllyBullets() noexcept {
    return ally_bullets;
}

} // namespace AIP
