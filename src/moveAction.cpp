#include "moveAction.h"
#include <iostream>

void MoveAction::moveShape(Move _move, ShapePart *_part) {
  move = _move;
  part = _part;
}

void MoveAction::doAction(Circle *circle) {
  if(part == nullptr)
    moveCircle(circle);
  else if(part == circle->getCenter())
    moveCircleCenter(circle, circle->getCenter());
  else if(part == circle->getRing())
    moveCircleRing(circle, circle->getRing());
}

void MoveAction::doAction(Polygon *polygon) {
  if(part == nullptr) {
    movePolygon(polygon);
  }
  else {
    Vertex *vertex = nullptr;
    polygon->map2Vertices([&vertex, this](Vertex *v) {
      if(part == v)
        vertex = v;
    });
    if(vertex != nullptr) {
      moveVertex(polygon, vertex);
    }
    else {
      Edge *edge = nullptr;
      polygon->map2Edges([&edge, this](Edge *e) {
        if (part == e)
          edge = e;
      });
      if(edge != nullptr)
        moveEdge(polygon, edge);
    }
  }
}

bool MoveAction::canDoAction(Circle *circle) {
  return true;
}

bool MoveAction::canDoAction(Polygon *polygon) {
  return true;
}

void MoveAction::moveVertex(Polygon *polygon, Vertex *vertex) {
  vertex->setPos(move.newMousePos);
  std::cout << "vertex moved\n";
}
void MoveAction::moveEdge(Polygon *polygon, Edge *edge) {
  edge->getA()->setPos(edge->getA()->getPos() + move.delta);
  edge->getB()->setPos(edge->getB()->getPos() + move.delta);
  std::cout << "edge moved\n";
}

void MoveAction::moveCircleCenter(Circle *circle, CircleCenter *circleCenter) {
  circleCenter->setPos(move.newMousePos);
  std::cout << "Circle center moved\n";
}
void MoveAction::moveCircleRing(Circle *circle, CircleRing *circleRing) {
  circleRing->setR(circleRing->getCenter()->getPos().dis(move.newMousePos));
  std::cout << "Circle ring moved\n";
}

void MoveAction::movePolygon(Polygon *polygon) {
  polygon->map2Vertices([this](Vertex *v) {
    v->setPos(v->getPos()+move.delta);
  });
  std::cout << "Polygon moved\n";
}

void MoveAction::moveCircle(Circle *circle) {
  circle->getCenter()->setPos(circle->getCenter()->getPos() + move.delta);
  std::cout << "Circle moved\n";
}
