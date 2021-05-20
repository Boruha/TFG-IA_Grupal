/*
Copyright (C) <2020-2021> Borja Pozo Wals (Tw: @Chico_Riot | GitHub: Boruha)

This file is part of 'TFG: Gestión y manejo de comportamientos grupales 
de entidades en videojuegos'.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <main.hpp>

#include <game/man/GameManager.hpp>
#include <game/utils/GameConditions.hpp>

#include <chrono>
#include <iostream>

int main() {
  using timer = std::chrono::steady_clock;

  AIP::GameManager gameManager   { };
  GameConditions   gameCondition { GameConditions::Loop };

  //glock
  timer time           { };
  auto  lastUpdateTime { time.now() };
  auto  timeElapse     { std::chrono::microseconds { 0 } };

  while (gameCondition != GameConditions::Cerrar) {
    timeElapse = std::chrono::duration_cast<std::chrono::microseconds>(time.now() - lastUpdateTime);

    if(timeElapse.count() >= gameManager.getLoopTime().number) {
      lastUpdateTime = time.now();
      gameCondition  = gameManager.update();
    }

    if(gameCondition == GameConditions::Victoria) {
      gameManager.clear();
      gameManager.loadNextLevel();
      gameManager.result = GameConditions::Loop; 
      gameCondition      = GameConditions::Loop;
    }

    if(gameCondition == GameConditions::Derrota) {
      gameManager.clear();
      gameManager.loadLevel0();
      gameManager.result = GameConditions::Loop; 
      gameCondition = GameConditions::Loop;
    }
  }
  
  return 0;
}