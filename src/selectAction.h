#pragma once

#include "shapeAction.h"

#include "shapePart.h"
#include "shape.h"

class SelectAction : public ShapeAction {
 private:
  Point p;

  bool selectWhole = false;

  ShapePart *selShapePart;
 public:
  SelectAction(Point _p);

  void collectResult(ShapePart **_selShapePart);
  void resetResult();

  virtual void doAction(Circle *circle);
  virtual void doAction(Polygon *polygon);

  virtual bool canDoAction(Circle *circle);
  virtual bool canDoAction(Polygon *polygon);
};
