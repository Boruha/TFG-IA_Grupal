#pragma once


//ARRIVE B.
constexpr const float ARRIVE_MIN_DIST   { 4 };
constexpr const float ARRIVE_MIN_DIST2  { ARRIVE_MIN_DIST * ARRIVE_MIN_DIST };

//FLOCKING B.
constexpr const float SEPARATION_RAD    { 30.f };
constexpr const float SEPARATION_FACTOR { 1.4f };   //tiene que se la mayor de las tres para asegurar no impacto
constexpr const float COHESION_FACTOR   { 1.2f };   //2da más grande para que se agrupen lo antes posible

//MOVEMENT_SYS
constexpr const float SEEK_MAX_SPEED { 100.f };
