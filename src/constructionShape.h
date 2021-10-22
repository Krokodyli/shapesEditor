#pragma once

#include "shape.h"

class ConstructionShape : public Shape {
public:
  ConstructionShape(Canvas *_canvas);
  virtual ~ConstructionShape() = 0;

  virtual void start(Point pos) = 0;
  virtual void moveConstructionPoint(Point newPos) = 0;
  virtual void putConstructionPoint() = 0;
  virtual bool canFinishConstruction() = 0;
  virtual Shape *finishShapeConstruction() = 0;

  virtual void doAction(ShapeAction *shapeAction) = 0;
  virtual bool canDoAction(ShapeAction *shapeAction) = 0;

  virtual void drawOnCanvas(CanvasDrawManager *drawManager) = 0;
  virtual void draw(DrawManager *drawManager) = 0;
};
