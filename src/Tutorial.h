#pragma once

#include "Object.h"

class Tutorial : public Object {
public:
  Tutorial();

  static void update();
  static Tutorial* currentTutorial;
};
