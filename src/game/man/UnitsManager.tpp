#include <game/man/UnitsManager.hpp>
#include <game/utils/AI_Constants.hpp>
#include <game/utils/ScreenData.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

inline void
UnitsManager::init() noexcept {
    loadLevel1();
}

inline void
UnitsManager::clear() noexcept {
    ent_man.clear();
    enemies_vec.clear();
    allies_vec.clear();
    ally_bullets.clear();
    enem_bullets.clear(); 
    player_id = 0u;
    singletonCmps = { };
}


inline void
UnitsManager::loadLevel0() { 
    enemies_vec.reserve(15);
    allies_vec.reserve(10);
    ally_bullets.reserve(20);
    enem_bullets.reserve(20);
    patrols.reserve(3);
    
    auto& pat1  = patrols.emplace_back();
    pat1.points = { fvec2<fint_t<int64_t>> 
        { { -920l }, { -550l } }
      , { { -750l }, { -150l } }
      , { { -430l }, {    0l } }
      , { { -250l }, { -300l } } 
    };

    auto& pat2  = patrols.emplace_back();
    pat2.points = { fvec2<fint_t<int64_t>> 
        { { -700l }, {  450l } }
      , { {  -50l }, { -150l } }
      , { {  300l }, { -150l } }
      , { {  300l }, {  450l } } 
    };

    auto& pat3  = patrols.emplace_back();
    pat3.points = { fvec2<fint_t<int64_t>> 
        { {  900l }, { -400l } }
      , { {  750l }, { -130l } }
      , { {    0l }, { -170l } }
      , { { -150l }, { -450l } } 
    };

    constexpr const int64_t sz { 20l };

    createPlayerPointer(sz, 400l, 400l, Color::Green);
    createCamera(UWIN_W, UWIN_H, 400l+(HALF_WIN_W * -1), 400l+(HALF_WIN_H * -1));

/*SQUAD 1*/
    createSoldier(sz, -940l, -420l, Color::Red, false, pat1);
    createSoldier(sz, -930l, -410l, Color::Red, false, pat1);
    createSoldier(sz, -920l, -430l, Color::Red, false, pat1);
    createArcher( sz, -950l, -430l, Color::Red, false, pat1);
    createArcher( sz, -930l, -450l, Color::Red, false, pat1);
/*SQUAD 2*/
    createSoldier(sz, -720l, 460l, Color::Red, false, pat2);
    createSoldier(sz, -780l, 450l, Color::Red, false, pat2);
    createSoldier(sz, -760l, 430l, Color::Red, false, pat2);
    createSoldier(sz, -740l, 410l, Color::Red, false, pat2);
    createArcher( sz, -730l, 450l, Color::Red, false, pat2);
/*SQUAD 3*/
    createSoldier(sz, 925l, -410l, Color::Red, false, pat3);
    createSoldier(sz, 880l, -420l, Color::Red, false, pat3);
    createArcher( sz, 940l, -430l, Color::Red, false, pat3);
    createArcher( sz, 900l, -370l, Color::Red, false, pat3);
    createArcher( sz, 890l, -380l, Color::Red, false, pat3);

/*TEAM*/
    createSoldier(sz, 380l, 390l, Color::Blue, true, pat1);
    createSoldier(sz, 360l, 400l, Color::Blue, true, pat1);
    createSoldier(sz, 400l, 420l, Color::Blue, true, pat1);
    createArcher( sz, 380l, 400l, Color::Blue, true, pat1);
    createArcher( sz, 420l, 380l, Color::Blue, true, pat1);
    createSoldier(sz, 380l, 420l, Color::Blue, true, pat1);
    createSoldier(sz, 300l, 420l, Color::Blue, true, pat1);
    createArcher( sz, 350l, 380l, Color::Blue, true, pat1);
    createArcher( sz, 340l, 380l, Color::Blue, true, pat1);
    createArcher( sz, 410l, 380l, Color::Blue, true, pat1);

/* OTHERS */
    createMessage(600l, 600l,"Esto es una prueba u know\n Controles:\n\tW -> UP\n\tA -> DOWN");
}

inline void
UnitsManager::loadLevel1() {
    enemies_vec.reserve(17);
    allies_vec.reserve(10);
    ally_bullets.reserve(20);
    enem_bullets.reserve(20);
    patrols.reserve(2);
    
    auto& pat1  = patrols.emplace_back();
    pat1.points = { fvec2<fint_t<int64_t>> 
        { { -1820l }, { -650l } }
      , { {  -950l }, {  150l } }
      , { {  -150l }, { -650l } }
      , { {  -950l }, { -850l } } 
    };

    auto& pat2  = patrols.emplace_back();
    pat2.points = { fvec2<fint_t<int64_t>> 
        { {  100l }, {  250l } }
      , { {  600l }, {   50l } }
      , { { 1400l }, { -700l } }
      , { {    0l }, { -400l } } 
    };

    constexpr const int64_t sz { 20l };

    createPlayerPointer(sz, -1800l, 820l, Color::Green);
    createCamera(UWIN_W, UWIN_H, -1800+(HALF_WIN_W * -1), 720l+(HALF_WIN_H * -1));

/*SQUAD 1*/
    createSoldier(sz, -1800l , -650l, Color::Red, false, pat1);
    createSoldier(sz, -1840l , -660l, Color::Red, false, pat1);
    createSoldier(sz, -1810l , -670l, Color::Red, false, pat1);
    createSoldier(sz, -1810l , -630l, Color::Red, false, pat1);
    createArcher( sz, -1830l , -675l, Color::Red, false, pat1);
    createArcher( sz, -1770l , -625l, Color::Red, false, pat1);
    createArcher( sz, -1820l , -650l, Color::Red, false, pat1);
/*SQUAD 2*/
    createSoldier(sz, 100l, 100l, Color::Red, false, pat2);
    createSoldier(sz, 120l, 100l, Color::Red, false, pat2);
    createSoldier(sz,  80l, 100l, Color::Red, false, pat2);
    createSoldier(sz, 110l, 120l, Color::Red, false, pat2);
    createSoldier(sz, 100l,  80l, Color::Red, false, pat2);
    createArcher( sz, 100l, 130l, Color::Red, false, pat2);
    createArcher( sz,  90l,  90l, Color::Red, false, pat2);
    createArcher( sz, 130l, 130l, Color::Red, false, pat2);
    createArcher( sz, 100l, 140l, Color::Red, false, pat2);
    createArcher( sz, 120l,  70l, Color::Red, false, pat2);

/*TEAM*/
    createSoldier(sz, -1830l, 820l, Color::Blue, true, pat1);
    createSoldier(sz, -1820l, 810l, Color::Blue, true, pat1);
    createSoldier(sz, -1820l, 830l, Color::Blue, true, pat1);
    createSoldier(sz, -1810l, 800l, Color::Blue, true, pat1);
    createSoldier(sz, -1830l, 800l, Color::Blue, true, pat1);
    createArcher( sz, -1820l, 790l, Color::Blue, true, pat1);
    createArcher( sz, -1800l, 850l, Color::Blue, true, pat1);
    createArcher( sz, -1800l, 780l, Color::Blue, true, pat1);
    createArcher( sz, -1780l, 820l, Color::Blue, true, pat1);
    createArcher( sz, -1790l, 770l, Color::Blue, true, pat1);

/*OTHERS*/
    createTiggerBox(30u, 40u, 500l, -800l, GameConditions::Victoria);
}

/* CREATES & DELETE */
inline void
UnitsManager::createSoldier(const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col, bool team, Patrol_t& pat) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    if(team)
        allies_vec.push_back(new_ent);
    else    
        enemies_vec.push_back(new_ent);

    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }    ) );
    ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent,    size  ,  size   , col) );
    ent_man.addComponentToEntity( new_ent, Collider2DCmp(     new_ent,    size  ,  size        ) );
    ent_man.addComponentToEntity( new_ent, CombatComponent(   new_ent, Combat_t::Soldier, team ) );
    ent_man.addComponentToEntity( new_ent, AI_Component(      new_ent, pat.begin()             ) );
}

inline void
UnitsManager::createArcher(const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col, bool team, Patrol_t& pat) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    if(team)
        allies_vec.push_back(new_ent);
    else    
        enemies_vec.push_back(new_ent);

    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }    ) );
    ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent,    size  ,  size   , col) );
    ent_man.addComponentToEntity( new_ent, Collider2DCmp(     new_ent,    size  ,  size        ) );
    ent_man.addComponentToEntity( new_ent, CombatComponent(   new_ent, Combat_t::Archer, team  ) );
    ent_man.addComponentToEntity( new_ent, AI_Component(      new_ent, pat.begin()             ) );
}

inline void
UnitsManager::createPlayerPointer(const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }     ) );
    ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent,    size  ,  size   , col ) );
    ent_man.addComponentToEntity( new_ent, Collider2DCmp(     new_ent,    size  ,  size         ) );
    ent_man.addComponentToEntity( new_ent, TeamComponent(     new_ent ) );

    player_id = new_ent;
}

inline void
UnitsManager::createCamera(const uint32_t sz_x, const uint32_t sz_y, const int64_t pos_x, const int64_t pos_y) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y } ) );
    ent_man.addComponentToEntity( new_ent, Collider2DCmp(     new_ent,    sz_x  ,  sz_y     ) );
    
    camera_id = new_ent;
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
UnitsManager::createTiggerBox(const uint32_t sz_x, const uint32_t sz_y, const int64_t pos_x, const int64_t pos_y, GameConditions event) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( new_ent, Collider2DCmp(     new_ent,   sz_x   ,   sz_y  ) );
    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }              ) );
    ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent,   sz_x   ,   sz_y  , Color::White ) );
    ent_man.addComponentToEntity( new_ent, TriggerCmp_t(      new_ent,   event  ) );
}

inline void
UnitsManager::createMessage(const int64_t pos_x, const int64_t pos_y, std::string mensaje) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( new_ent, Collider2DCmp(     new_ent,   20u    ,   20u     ) );
    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y } ) );
    ent_man.addComponentToEntity( new_ent, TextCmp_t(         new_ent, mensaje  ) );
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

inline BECS::entID  
UnitsManager::getCameraID() noexcept { 
    return camera_id; 
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
