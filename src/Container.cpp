#include "Container.h"

Container::Container(std::vector<Object*> objects) : objects(objects) {}

void Container::changeVisibility(bool visible) {
  for (Object* object : objects) {
    object->visible = visible;
  }
}
