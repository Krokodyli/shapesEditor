#pragma once

#include <vector>

#include "canvasManagerState.h"
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

  CanvasManagerState *state;
public:
  NewVertexAction(ShapePart *_shapePart, CanvasManagerState *_state);

  virtual void doAction(Circle *circle);
  virtual void doAction(Polygon *polygon);

  virtual bool canDoAction(Circle *circle);
  virtual bool canDoAction(Polygon *polygon);
};
