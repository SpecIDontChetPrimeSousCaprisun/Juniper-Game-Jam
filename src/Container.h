#pragma once

#include "Object.h"
#include <vector>
#include <map>

class Container {
public:
  Container(std::vector<Object*> objects);
  
  static void deletePendingObjects();

  void changeVisibility(bool visible);
  void changeCollisions(bool visible);
  void changeCornerRadius(float radius);
  void revertCollisions();
  void registerObjects();
  void clear();
  void pendDelete();
  void cancelDelete();
  bool isDeleted();

  std::vector<Object*> objects;
private:
  static std::vector<Container*> containers;

  bool pendingDelete;
  std::map<Object*, bool> oldCollisions;
};
