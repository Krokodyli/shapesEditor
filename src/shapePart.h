#pragma once

#include "canvasDrawManager.h"
#include "point.h"
#include "appConsts.h"

class Shape;

class ShapePart {
 protected:
  Shape *parent;
  Color color;
 public:
  ShapePart(Shape *_parent);
  virtual ~ShapePart();

  Shape *getParent();

  void setColor(Color _color);
  Color getColor();

  virtual bool isUnderPoint(Point p) = 0;

  virtual void drawOnCanvas(CanvasDrawManager *drawManager) = 0;
  virtual void draw(DrawManager *drawManager) = 0;
};
