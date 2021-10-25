#include "moveAction.h"
#include "constraint.h"
#include "canvasManagerState.h"
#include "canvas.h"
#include "shapePart.h"
#include "vertex.h"
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
  Point prevPos = vertex->getPos();
  vertex->setPos(fixPoint(move.newMousePos, vertex));
  set<ShapePart*> s;

  auto constraint = state->getConstraint(vertex->getA());
  if(constraint != nullptr && constraint->isConstraintBroken()
     && !constraint->resolveConstraint(vertex, state, &s)) {
    vertex->setPos(prevPos);
    movePolygon(polygon);
  }

  constraint = state->getConstraint(vertex->getB());
  if (constraint != nullptr && constraint->isConstraintBroken() &&
      !constraint->resolveConstraint(vertex, state, &s)) {
    vertex->setPos(prevPos);
    movePolygon(polygon);
  }
}

void MoveAction::moveEdge(Polygon *polygon, Edge *edge) {
  Vertex *a = edge->getA();
  Vertex *b = edge->getB();
  Point delta = move.delta;
  Point prevAPos = a->getPos();
  Point prevBPos = b->getPos();
  Point newAPos = fixPoint(prevAPos + delta, edge);
  delta = newAPos - prevAPos;
  Point newBPos = fixPoint(prevBPos + delta, edge);
  delta = newBPos - prevBPos;
  newAPos = prevAPos + delta;
  newBPos = prevBPos + delta;

  set<ShapePart *> s;

  a->setPos(newAPos);
  b->setPos(newBPos);

  auto constraint = state->getConstraint(a->getOtherEdge(edge));
  s.insert(b);
  if (constraint != nullptr && constraint->isConstraintBroken() &&
      !constraint->resolveConstraint(a, state, &s)) {
    a->setPos(prevAPos);
    b->setPos(prevBPos);
    movePolygon(polygon);
  }
  s.erase(b);

  constraint = state->getConstraint(b->getOtherEdge(edge));
  s.insert(a);
  if (constraint != nullptr && constraint->isConstraintBroken() &&
      !constraint->resolveConstraint(b, state, &s)) {
    a->setPos(prevAPos);
    b->setPos(prevBPos);
    movePolygon(polygon);
  }
  s.erase(b);

  constraint = state->getConstraint(edge);
  if (constraint != nullptr && constraint->isConstraintBroken() &&
      !constraint->resolveConstraint(edge, state, &s)) {
    a->setPos(prevAPos);
    b->setPos(prevBPos);
    movePolygon(polygon);
  }
}

void MoveAction::moveCircleCenter(Circle *circle, CircleCenter *circleCenter) {
  Point prevPos = circleCenter->getPos();
  int r = circle->getRing()->getR();
  Point minPoint = Point(r, r);
  Point maxPoint = circle->getCanvas()->getSize() - Point (r, r);
  circleCenter->setPos(move.newMousePos.fix2Rec(minPoint, maxPoint));

  auto constraint = state->getConstraint(circleCenter);
  set<ShapePart *> s;

  if(circle->isShapeOutsideCanvas()
     || (constraint != nullptr &&
         !constraint->resolveConstraint(circleCenter, state, &s)))
    circleCenter->setPos(prevPos);
}

void MoveAction::moveCircleRing(Circle *circle, CircleRing *circleRing) {
  int prevR = circleRing->getR();
  circleRing->setR(circleRing->getCenter()->getPos().dis(move.newMousePos));

  auto constraint = state->getConstraint(circleRing);
  set<ShapePart *> s;

  if(circle->isShapeOutsideCanvas()
     || (constraint != nullptr
         && !constraint->resolveConstraint(circleRing, state, &s)))
    circleRing->setR(prevR);
}

void MoveAction::movePolygon(Polygon *polygon) {
  Point maxDelta = move.delta;

  vector<Point> oldPos;
  vector<std::pair<Constraint*, Edge*>> constraints;

  polygon->map2Vertices([this, &maxDelta, &oldPos](Vertex *v) {
    oldPos.push_back(v->getPos());
    Point vPos = v->getPos();
    Point nPos = vPos + maxDelta;
    nPos = fixPoint(nPos, v);
    maxDelta = nPos - vPos;
  });
  polygon->map2Edges([this, &constraints](Edge *e){
    if(state->getConstraint(e) != nullptr)
      constraints.push_back(std::make_pair(state->getConstraint(e), e));
  });

  polygon->map2Vertices([this, &maxDelta](Vertex *v) {
    v->setPos(v->getPos() + maxDelta);
  });

  for(auto entry : constraints) {
    auto constraint = entry.first;
    auto edge = entry.second;
    set<ShapePart*> s;
    if(!constraint->resolveConstraint(edge, state, &s)) {
      int i = 0;
      polygon->map2Vertices([this, &oldPos, &i](Vertex *v){
        v->setPos(oldPos[i]);
        i++;
      });
    }
  }
}

void MoveAction::moveCircle(Circle *circle) {
  moveCircleCenter(circle, circle->getCenter());
}

Point MoveAction::fixPoint(Point p, ShapePart *part) {
  return p.fix2Rec(Point(0, 0),
                   part->getParent()->getCanvas()->getSize());
}

Point MoveAction::fixPoint(Point p, Shape *shape) {
  return p.fix2Rec(Point(0, 0), shape->getCanvas()->getSize());
}
