#pragma once

#include "Object.h"
#include <random>

class Particle : public Object {
public:
  Particle(glm::vec2 position, glm::vec2 size, float transparency, std::string texPath, 
           glm::vec2 direction, float spread, float lifetime);
protected:
  void afterUpdate() override;
private:
  static std::mt19937 rng;

  glm::vec2 direction;
  float spread, lifetime;
};
