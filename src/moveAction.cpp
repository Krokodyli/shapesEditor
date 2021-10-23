#include "moveAction.h"
#include "constraint.h"
#include "canvasManagerState.h"
#include <iostream>

void MoveAction::moveShape(Move _move, CanvasManagerState *_state,
                           ShapePart *_part) {
  move = _move;
  state = _state;
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
}

void MoveAction::moveEdge(Polygon *polygon, Edge *edge) {
  edge->getA()->setPos(edge->getA()->getPos() + move.delta);
  edge->getB()->setPos(edge->getB()->getPos() + move.delta);
}

void MoveAction::moveCircleCenter(Circle *circle, CircleCenter *circleCenter) {
  Point prevPos = circleCenter->getPos();
  circleCenter->setPos(move.newMousePos);

  auto constraint = state->getConstraint(circleCenter);

  if(circle->isShapeOutsideCanvas()
     || (constraint != nullptr && constraint->isConstraintBroken()))
    circleCenter->setPos(prevPos);
}
void MoveAction::moveCircleRing(Circle *circle, CircleRing *circleRing) {
  int prevR = circleRing->getR();
  circleRing->setR(circleRing->getCenter()->getPos().dis(move.newMousePos));

  auto constraint = state->getConstraint(circleRing);

  if(circle->isShapeOutsideCanvas()
     || (constraint != nullptr && constraint->isConstraintBroken()))
    circleRing->setR(prevR);
}

void MoveAction::movePolygon(Polygon *polygon) {
  polygon->map2Vertices([this](Vertex *v) {
    v->setPos(v->getPos()+move.delta);
  });
}

void MoveAction::moveCircle(Circle *circle) {
  moveCircleCenter(circle, circle->getCenter());
}
