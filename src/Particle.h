#pragma once

#include "Object.h"

class Particle : public Object {
public:
  Particle(glm::vec2 position, glm::vec2 size, float transparency, std::string texPath, 
           glm::vec2 direction, float spread, float lifetime);
protected:
  void afterUpdate() override;
private:
  glm::vec2 direction;
  float spread, lifetime;
};
