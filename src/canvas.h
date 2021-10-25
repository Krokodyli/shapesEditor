#pragma once

#include <vector>

#include "drawManager.h"
#include "canvasDrawManager.h"
#include "inputInfo.h"
#include "polygon.h"
#include "shape.h"
#include "canvasAction.h"
#include "circle.h"

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

  void doAction(CanvasAction *canvasAction);
  bool canDoAction(CanvasAction *canvasAction);

  void draw(DrawManager *drawManager);

  Point getPos();
  Point getSize();

  Polygon *addPolygon(vector<Point> points);
  Circle *addCircle(Point center, int r);
};
