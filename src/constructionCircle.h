#pragma once

#include "constructionShape.h"

class ConstructionCircle : public ConstructionShape {
 private:
  Point center;
  int radius;

  bool isCenterPut;
  bool isRingPut;
 public:
  ConstructionCircle(Canvas *_canvas);
  virtual ~ConstructionCircle();

  virtual void start(Point pos);
  virtual void moveConstructionPoint(Point newPos);
  virtual void putConstructionPoint();
  virtual bool canFinishConstruction();
  virtual Shape *finishShapeConstruction();

  virtual void doAction(ShapeAction *shapeAction);
  virtual bool canDoAction(ShapeAction *shapeAction);

  virtual void drawOnCanvas(CanvasDrawManager *drawManager);
  virtual void draw(DrawManager *drawManager);
};
