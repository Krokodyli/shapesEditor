#pragma once

#include <vector>

#include "drawManager.h"
#include "canvasDrawManager.h"
#include "inputInfo.h"
#include "shape.h"

using std::vector;

class CanvasManager;

class Canvas {
  Point pos;
  Point size;
  CanvasDrawManager *canvasDrawManager;

  vector<Shape*> shapes;
 public:
  Canvas(Point _pos, Point _size, CanvasDrawManager *_canvasDrawManager);
  ~Canvas();

  void draw(DrawManager *drawManager);
  void update(CanvasManager *canvasManager, InputInfo *inputInfo);
};
