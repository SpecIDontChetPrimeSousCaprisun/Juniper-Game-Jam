#include "Tutorial.h"

Tutorial::Tutorial() : Object(glm::vec2(0.0f, -1000.0f), glm::vec2(100.0f, 100.0f), 0.0f, "textures/player.png", -1) {
  anchored = true;
  canCollide = false;
}
