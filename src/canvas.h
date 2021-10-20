#pragma once

#include "drawManager.h"
#include "canvasDrawManager.h"
#include "inputInfo.h"

class CanvasManager;

class Canvas {
  Point pos;
  Point size;
  CanvasDrawManager *canvasDrawManager;
 public:
  Canvas(Point _pos, Point _size, CanvasDrawManager *_canvasDrawManager);
  ~Canvas();

  void draw(DrawManager *drawManager);
  void update(CanvasManager *canvasManager, InputInfo *inputInfo);
};
