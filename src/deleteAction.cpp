#include "deleteAction.h"

#include "constraint.h"
#include "shapePart.h"
#include "polygon.h"
#include "canvasManagerState.h"
#include "circle.h"

DeleteAction::DeleteAction(CanvasManagerState *_state,
                           ShapePart *_shapePart) : state(_state),
                                                    shapePart(_shapePart),
                                                    deleteWholeShape(false) { }

bool DeleteAction::isDeletingWholeShapeNeeded() {
  return deleteWholeShape;
}

void DeleteAction::doAction(Circle *circle) {
  deleteWholeCircle(circle);
}

void DeleteAction::doAction(Polygon *polygon) {
  if(shapePart == nullptr) {
    deleteWholePolygon(polygon);
  }
  else {
    if(countSides(polygon) > 3)
      deletePolygonPart(polygon);
    else
      deleteWholePolygon(polygon);
  }
}

bool DeleteAction::canDoAction(Circle *circle) {
  return true;
}

bool DeleteAction::canDoAction(Polygon *polygon) {
  return true;
}

void DeleteAction::deleteWholeCircle(Circle *circle) {
  state->deleteConstraint(circle->getCenter());
  state->deleteConstraint(circle->getRing());
  deleteWholeShape = true;
}

void DeleteAction::deleteWholePolygon(Polygon *polygon) {
  deleteWholeShape = true;
  polygon->map2Vertices([this](Vertex *v) {
    this->state->deleteConstraint(v);
  });
  polygon->map2Edges([this](Edge *e) {
    this->state->deleteConstraint(e);
  });
}

void DeleteAction::deletePolygonPart(Polygon *polygon) {
  Vertex *vertex = nullptr;
  polygon->map2Vertices([&vertex, this](Vertex *v) {
    if(vertex == nullptr && v == this->shapePart)
      vertex = v;
  });
  if(vertex != nullptr) {
    deleteVertex(polygon, vertex);
  }
  else {
    Edge *edge = nullptr;
    polygon->map2Edges([&edge, this](Edge *e) {
      if (edge == nullptr && e == this->shapePart)
        edge = e;
    });
    if(edge != nullptr) {
      deleteEdge(polygon, edge);
    }
  }
}

void DeleteAction::deleteVertex(Polygon *polygon, Vertex *v) {
  // e1 - v - e - v2
  Edge *e = v->getB();

  Edge *e1 = v->getA();
  Vertex *v2 = e->getB();
  e1->setB(v2);
  v2->setA(e1);
  if(v == polygon->getHead()) {
    polygon->setHead(v->getA()->getA());
  }
  state->deleteConstraint(v);
  state->deleteConstraint(e);
  delete v;
  delete e;
}

void DeleteAction::deleteEdge(Polygon *polygon, Edge *e) {
  deleteVertex(polygon, e->getA());
}

int DeleteAction::countSides(Polygon *polygon) {
  int verticesCount = 0;
  polygon->map2Vertices([&verticesCount](Vertex *v) {
    verticesCount++;
  });
  return verticesCount;
}
