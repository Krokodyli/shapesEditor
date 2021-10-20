#pragma once

#include "drawManager.h"
#include "inputInfo.h"

class CanvasManager;

class Canvas {
 public:
   void draw(DrawManager *drawManager);
   void update(CanvasManager *canvasManager, InputInfo *inputInfo);
};
