#include "toolbar.h"
#include <iostream>

void Toolbar::draw(DrawManager *drawManager){
  drawManager->drawRect(0, 0, 200, 600, Color(0, 200, 0));
}
