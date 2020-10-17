#pragma once


//ARRIVE B.
constexpr const float ENT_ARRIVE_MIN_DIST   { 10.f };
constexpr const float ENT_ARRIVE_MIN_DIST2  { ENT_ARRIVE_MIN_DIST * ENT_ARRIVE_MIN_DIST };

constexpr const float FLOCK_ARRIVE_MIN_DIST   { 40.f };
constexpr const float FLOCK_ARRIVE_MIN_DIST2  { FLOCK_ARRIVE_MIN_DIST * FLOCK_ARRIVE_MIN_DIST };

//FLOCKING B. TODO: CALCULAR EL FUNCION DEL TAMAÑO DE LA ENTIDAD.
constexpr const float SEPARATION_RAD  { 50.f };
constexpr const float SEPARATION_RAD2 { SEPARATION_RAD * SEPARATION_RAD };

constexpr const float SEPARATION_NUM  { 100000.f };

constexpr const float COHESION_RAD    { 30.f };
constexpr const float COHESION_RAD2   { COHESION_RAD * COHESION_RAD };

//MOVEMENT_SYS
constexpr const float ENT_MAX_SPEED { 100.f };
