#pragma once

#include "shapePart.h"

class Shape;
class CircleRing;

class CircleCenter : public ShapePart {
 private:
  Point pos;
  CircleRing *circleRing;
 public:
  CircleCenter(Point _pos, Shape *_parent, CircleRing *_circleRing = nullptr);
  virtual ~CircleCenter();

  CircleRing *getCircleRing();
  void setCircleRing(CircleRing *_circleRing);

  Point getPos();
  void setPos(Point _pos);

  virtual bool isUnderPoint(Point p);

  virtual void drawOnCanvas(CanvasDrawManager *drawManager);
  virtual void draw(DrawManager *drawManager);
};
