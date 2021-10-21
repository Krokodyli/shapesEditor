#pragma once

class Polygon;
class Circle;

class ShapeAction {
 public:
  virtual void doAction(Circle *circle) = 0;
  virtual void doAction(Polygon *polygon) = 0;

  virtual bool canDoAction(Circle *circle) = 0;
  virtual bool canDoAction(Polygon *polygon) = 0;
};
