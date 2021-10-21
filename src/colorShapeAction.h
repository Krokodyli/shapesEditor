#pragma once

#include "shapeAction.h"
#include "color.h"

class Polygon;
class Circle;

class ColorShapeAction : public ShapeAction {
  Color color;
public:
  ColorShapeAction(Color _color);

  virtual void doAction(Circle *circle);
  virtual void doAction(Polygon *polygon);

  virtual bool canDoAction(Circle *circle);
  virtual bool canDoAction(Polygon *polygon);
};
