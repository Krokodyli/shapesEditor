#include "deleteAction.h"

#include "shapePart.h"
#include "polygon.h"

DeleteAction::DeleteAction(ShapePart *_shapePart) : shapePart(_shapePart),
                                                    deleteWholeShape(false) { }

bool DeleteAction::isDeletingWholeShapeNeeded() {
  return deleteWholeShape;
}

void DeleteAction::doAction(Circle *circle) {
  deleteWholeShape = true;
}

void DeleteAction::doAction(Polygon *polygon) {
  if(shapePart == nullptr) {
    deleteWholeShape = true;
  }
  else {
    int verticesCount = 0;
    polygon->map2Vertices([&verticesCount](Vertex *v) {
      verticesCount++;
    });
    if(verticesCount <= 3) {
      deleteWholeShape = true;
    }
    else {
      deletePolygonPart(polygon);
    }
  }
}

bool DeleteAction::canDoAction(Circle *circle) {
  return true;
}

bool DeleteAction::canDoAction(Polygon *polygon) {
  return true;
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
    if(edge != nullptr)
      deleteEdge(polygon, edge);
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
  delete v;
  delete e;
}

void DeleteAction::deleteEdge(Polygon *polygon, Edge *e) {
  deleteVertex(polygon, e->getA());
}
