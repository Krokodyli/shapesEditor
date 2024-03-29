#pragma once

#include <vector>

#include "constraint.h"
#include "shapeAction.h"

using std::vector;

class Shape;
class ShapePart;
class Edge;
class Vertex;

class DeleteAction : public ShapeAction {
 private:
  CanvasManagerState *state;
  ShapePart *shapePart;
  bool deleteWholeShape;

  void deleteWholeCircle(Circle *circle);

  void deleteWholePolygon(Polygon *polygon);
  void deletePolygonPart(Polygon *polygon);
  void deleteVertex(Polygon *polygon, Vertex *v);
  void deleteEdge(Polygon *polygon, Edge *e);

  int countSides(Polygon *polygon);
 public:
   DeleteAction(CanvasManagerState *_state, ShapePart *_shapePart = nullptr);

   bool isDeletingWholeShapeNeeded();

   virtual void doAction(Circle *circle);
   virtual void doAction(Polygon *polygon);

   virtual bool canDoAction(Circle *circle);
   virtual bool canDoAction(Polygon *polygon);
};
