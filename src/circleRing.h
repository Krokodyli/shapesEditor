#pragma once

#include "shapePart.h"

class Shape;
class CircleCenter;

class CircleRing : ShapePart {
 private:
  int r;
  CircleCenter *center;
 public:
  CircleRing(int _r, Shape *_parent, CircleCenter *_center = nullptr);
  virtual ~CircleRing();

  int getR();
  void setR(int _r);
  CircleCenter *getCenter();
  void setCenter(CircleCenter *_center);

  virtual bool isUnderPoint(Point p);

  virtual void drawOnCanvas(CanvasDrawManager *drawManager);
  virtual void draw(DrawManager *drawManager);
};
