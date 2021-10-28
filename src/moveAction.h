#pragma once

#include <set>

#include "constraint.h"
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
  CanvasManagerState *state;

  Point fixPoint(Point p, ShapePart *part);
  Point fixPoint(Point p, Shape *shape);

  Edge *findEdge(Polygon *polygon, ShapePart *shapePart);
  Vertex *findVertex(Polygon *polygon, ShapePart *shapePart);

  void getVerticesPositions(Polygon *polygon, vector<Point> *oldPos);
  void getMaxDelta4Vertices(Polygon *polygon, Point *maxDelta);
  void getEdgesConstraints(Polygon *polygon,
                           vector<std::pair<Constraint*, Edge*>> *constraints);
  void moveAllVertices(Polygon *polygon, Point maxDelta);
  void restoreVerticesPositions(Polygon *polygon, vector<Point> *oldPos);
  void setNewVerticesPosForEdge(Polygon *polygon, Edge *edge,
                                Point *prevAPos, Point *prevBPos);
public:
  virtual void moveShape(Move _move, CanvasManagerState *_state,
                         ShapePart *_part = nullptr);

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
