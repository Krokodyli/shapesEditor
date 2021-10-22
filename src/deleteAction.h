#pragma once

#include <vector>

#include "shapeAction.h"

using std::vector;

class Shape;
class ShapePart;
class Edge;
class Vertex;

class DeleteAction : public ShapeAction {
 private:
  ShapePart *shapePart;
  bool deleteWholeShape;

  void deletePolygonPart(Polygon *polygon);
  void deleteVertex(Polygon *polygon, Vertex *v);
  void deleteEdge(Polygon *polygon, Edge *e);
public:
  DeleteAction(ShapePart *_shapePart = nullptr);

  bool isDeletingWholeShapeNeeded();

  virtual void doAction(Circle *circle);
  virtual void doAction(Polygon *polygon);

  virtual bool canDoAction(Circle *circle);
  virtual bool canDoAction(Polygon *polygon);
};
