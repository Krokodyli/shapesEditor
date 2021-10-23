#pragma once

#include <vector>

#include "shapeAction.h"

using std::vector;

class Shape;
class ShapePart;
class Edge;
class Vertex;

class NewVertexAction : public ShapeAction {
private:
  ShapePart *shapePart;

  void addVertex(Edge *e);
public:
  NewVertexAction(ShapePart *_shapePart);

  virtual void doAction(Circle *circle);
  virtual void doAction(Polygon *polygon);

  virtual bool canDoAction(Circle *circle);
  virtual bool canDoAction(Polygon *polygon);
};
