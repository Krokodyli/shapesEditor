#pragma once

#include <vector>

#include "constructionShape.h"

using std::vector;

class ConstructionPolygon : public ConstructionShape {
protected:
  vector<Point> points;
  bool shouldFinish;
public:
  ConstructionPolygon(Canvas *_canvas);
  virtual ~ConstructionPolygon();

  virtual void start(Point pos);
  virtual void moveConstructionPoint(Point newPos);
  virtual void putConstructionPoint();
  virtual bool canFinishConstruction();
  virtual Shape *finishShapeConstruction();

  virtual void doAction(ShapeAction *shapeAction);
  virtual bool canDoAction(ShapeAction *shapeAction);

  virtual void drawOnCanvas(CanvasDrawManager *drawManager);
  virtual void draw(DrawManager *drawManager);

  virtual bool isShapeOutsideCanvas();
};
