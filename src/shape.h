#pragma once

#include "point.h"
#include "shapePart.h"

class ShapeAction;
class Canvas;

class Shape {
 protected:
  Canvas *canvas;
 public:
  Shape(Canvas *_canvas);
  virtual ~Shape();

  virtual void doAction(ShapeAction *shapeAction) = 0;
  virtual bool canDoAction(ShapeAction *shapeAction) = 0;

  virtual void drawOnCanvas(CanvasDrawManager *drawManager) = 0;
  virtual void draw(DrawManager *drawManager) = 0;

  virtual bool isShapeOutsideCanvas() = 0;
  virtual Canvas *getCanvas();
};
