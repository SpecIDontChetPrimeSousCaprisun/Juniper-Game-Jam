#pragma once

#include <map>
#include <iostream>
#include <vector>
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct drawInfo {
public:
  drawInfo(glm::vec2 position, glm::vec2 size);

  glm::vec2 position, size;
};

class Object {
public:
  Object(const Object&) = delete;
  Object& operator=(const Object&) = delete;

  Object(glm::vec2 position, glm::vec2 size, float transparency, std::string texPath, int zIndex);
  virtual ~Object();

  static void initShader();
  static void updateAll();
  static void drawAll();
  static Object* raycast(
                          glm::vec2 origin,
                          const glm::vec2& direction,
                          glm::vec2& hitPoint,
                          float& tHit,
                          const std::vector<Object*>& ignore
                        );

  glm::vec2 position, size, linearVelocity;
  float transparency, rotation;
  bool visible, anchored, canCollide;
  int zIndex;
protected:
  virtual drawInfo* beforeDrawing(drawInfo* info);
  virtual void afterDrawing(drawInfo* info);
private:
  static std::map<int, std::vector<Object*>> objects;
  static unsigned int shaderProgram;

  unsigned int VAO, VBO, texture;

  void init();
  void update();
  void draw(); 
};
