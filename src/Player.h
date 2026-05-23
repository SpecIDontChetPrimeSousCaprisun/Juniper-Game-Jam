#pragma once

#include "Object.h"

class Player : public Object {
public:
  Player(glm::vec2 position, glm::vec2 size, float transparency, std::string texPath, int zIndex, bool isCurrentPlayer);
  
  static void update();

  static Player* currentPlayer;
};
