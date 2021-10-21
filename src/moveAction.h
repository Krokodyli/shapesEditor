#pragma once

#include <set>

#include "shapeAction.h"
#include "selectShapeCanvasAction.h"
#include "shapePart.h"
#include "shape.h"
#include "move.h"
#include "polygon.h"
#include "circle.h"

class MoveAction : public ShapeAction {
  Move move;

  ShapePart *part;
  Shape *shape;
 public:
  virtual void moveShape(Move _move, ShapePart *_part = nullptr);

  virtual void doAction(Circle *circle);
  virtual void doAction(Polygon *polygon);

  virtual bool canDoAction(Circle *circle);
  virtual bool canDoAction(Polygon *polygon);

  void moveVertex(Polygon *polygon, Vertex *vertex);
  void moveEdge(Polygon *polygon, Edge *edge);

  void moveCircleCenter(Circle *circle, CircleCenter *circleCenter);
  void moveCircleRing(Circle *circle, CircleRing *circleRing);

  void movePolygon(Polygon *polygon);
  void moveCircle(Circle *circle);
};
