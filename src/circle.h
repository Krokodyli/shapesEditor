#pragma once

#include "shape.h"
#include "circleCenter.h"
#include "circleRing.h"

class ShapeAction;
class Canvas;

class Circle : public Shape {
  CircleCenter *center;
  CircleRing *ring;
public:
  Circle(Point pos, int r, Canvas *_canvas);
  virtual ~Circle();

  CircleCenter *getCenter();
  CircleRing *getRing();

  virtual void doAction(ShapeAction *shapeAction);
  virtual bool canDoAction(ShapeAction *shapeAction);

  virtual void drawOnCanvas(CanvasDrawManager *drawManager);
  virtual void draw(DrawManager *drawManager);

  virtual bool isShapeOutsideCanvas();
};
