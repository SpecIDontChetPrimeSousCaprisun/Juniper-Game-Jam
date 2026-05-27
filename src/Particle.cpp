#include "Particle.h"
#include "Window.h"

std::mt19937 Particle::rng(std::random_device{}());

Particle::Particle(glm::vec2 position, glm::vec2 size, float transparency, std::string texPath, 
                   glm::vec2 direction, float spread, float lifetime) 
  : Object(position, size, transparency, texPath, 999), direction(direction), spread(spread), lifetime(lifetime) {
  anchored = false;

  std::uniform_real_distribution<float> dist(-spread, spread);

  linearVelocity = direction + glm::vec2(dist(rng), dist(rng));
}

void Particle::afterUpdate() {
  lifetime -= Window::deltaTime;

  if (lifetime <= 0) {
    pendingDelete = true;
  }
}
