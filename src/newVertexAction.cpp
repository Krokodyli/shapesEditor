#include "newVertexAction.h"
#include "canvasManagerState.h"
#include "polygon.h"

NewVertexAction::NewVertexAction(ShapePart *_shapePart,
                                 CanvasManagerState *_state)
  : shapePart(_shapePart), state(_state) { }

void NewVertexAction::doAction(Circle *circle) { }

void NewVertexAction::doAction(Polygon *polygon) {
  Edge *e = nullptr;
  polygon->map2Edges([&e, this](Edge *edge) {
    if(e == nullptr && edge == shapePart)
      e = edge;
  });
  if(e != nullptr)
    addVertex(e);
}

bool NewVertexAction::canDoAction(Circle *circle) {
  return false;
}

bool NewVertexAction::canDoAction(Polygon *polygon) {
  Edge *e = nullptr;
  polygon->map2Edges([&e, this](Edge *edge) {
    if (e == nullptr && edge == shapePart)
      e = edge;
  });
  if (e != nullptr)
    return true;
  return false;
}

void NewVertexAction::addVertex(Edge *e) {
  // a - e - b - e2
  // a - e - v - e1 - b - e2
  state->deleteConstraint(e);
  Vertex *a = e->getA(), *b = e->getB();
  Point pos = (a->getPos() + b->getPos()) / 2;
  Vertex *v = new Vertex(pos, e->getParent(), e);
  Edge *e1 = new Edge(e->getParent(), v, b);
  v->setB(e1);
  e->setB(v);
  b->setA(e1);
}
