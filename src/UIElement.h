#pragma once

#include "Object.h"

class UIElement : public Object {
public:
  UIElement(glm::vec2 position, glm::vec2 size, float transparency, std::string texPath, int zIndex);

  glm::vec2 anchorPoint;
protected:
  virtual drawInfo* beforeDrawing(drawInfo* info) override;
  drawInfo* baseBeforeDrawing(drawInfo* info); 
};
