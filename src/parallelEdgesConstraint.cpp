#include "parallelEdgesConstraint.h"
#include "edge.h"
#include "vertex.h"
#include "shape.h"
#include "canvas.h"
#include <iostream>

ParallelEdgesConstraint::ParallelEdgesConstraint(Edge *_a, Edge *_b)
  : a(_a), b(_b) { }

ParallelEdgesConstraint::~ParallelEdgesConstraint() {}

bool ParallelEdgesConstraint::isConstraintBroken() {
  double ar = a->getLeanRatio();
  double br = b->getLeanRatio();
  return abs(ar - br) > 0.02;
}

bool ParallelEdgesConstraint::resolveConstraint(ShapePart *p,
                                                CanvasManagerState *state,
                                                set<ShapePart *> *resolved) {
  if (!isConstraintBroken() || p == a || p == b)
    return true;

  if (resolved->find(p) != resolved->end())
    return false;
  resolved->insert(p);

  Edge *edge = getEdgeFromVertex(p);
  Edge *otherEdge = getOtherEdge(edge);

  if (resolveWithVertex(otherEdge, edge->getLeanRatio(), otherEdge->getA(),
                        state, resolved)) {
    resolved->erase(p);
    return true;
  }

  if (resolveWithVertex(otherEdge, edge->getLeanRatio(), otherEdge->getB(),
                        state, resolved)) {
    resolved->erase(p);
    return true;
  }

  resolved->erase(p);
  return false;
}

vector<ShapePart *> ParallelEdgesConstraint::getAllConstrainted() {
  return vector<ShapePart*>{ a, b };
}

void ParallelEdgesConstraint::draw(DrawManager *drawManager, ShapePart *part) {
  Edge *edge = nullptr;

  if (part == a)
    edge = a;
  else if (part == b)
    edge = b;

  if(edge != nullptr) {
    int size = AppConsts::constraintIconSize;
    Point m = (edge->getA()->getPos() + edge->getB()->getPos()) /2;
    drawManager->drawRect(m.x - size/2, m.y - size/2, size, size, color);
    drawManager->drawImage(m.x - size / 2, m.y - size / 2,
                          AppConsts::lockedIconImage);
  }
}

bool ParallelEdgesConstraint::resolveWithVertex(Edge *edge, double expRatio,
                                             Vertex *v,
                                             CanvasManagerState *state,
                                             set<ShapePart*> *resolved) {
  if(resolved->find(v) != resolved->end())
    return false;
  resolved->insert(v);

  Vertex *other = edge->getOtherVertex(v);

  Point prevPos = other->getPos();
  Point newPosForOther = calculateRightPosition(v, other, expRatio);
  newPosForOther = newPosForOther.fix2Rec(Point(0, 0),
                                          v->getParent()->getCanvas()->getSize());
  other->setPos(newPosForOther);

  Edge *otherEdge = other->getOtherEdge(edge);
  auto otherEdgeConstraint = state->getConstraint(otherEdge);
  if (otherEdgeConstraint != nullptr &&
      !otherEdgeConstraint->resolveConstraint(other, state, resolved)) {
    other->setPos(prevPos);
    resolved->erase(v);
    return false;
  }
  if (!isConstraintBroken()) {
    resolved->erase(v);
    return true;
  }

  other->setPos(prevPos);
  resolved->erase(v);
  return false;
}

Point ParallelEdgesConstraint::calculateRightPosition(Vertex *locked,
                                                      Vertex *v,
                                                      double expRatio) {
  Point l = locked->getPos();
  Point p = v->getPos();
  double len = l.dis(p);
  if(l.y < p.y)
    return Point(l.x + cos(expRatio) * len, l.y + sin(expRatio) * len);
  else
    return Point(l.x - cos(expRatio) * len, l.y - sin(expRatio) * len);
}

Edge *ParallelEdgesConstraint::getEdgeFromVertex(ShapePart *part) {
  if (part == a->getA() || part == a->getB())
    return a;
  else if (part == b->getA() || part == b->getB())
    return b;
  else
    return nullptr;
}

Edge *ParallelEdgesConstraint::getOtherEdge(Edge *e) {
  if (e == a)
    return b;
  else if (e == b)
    return a;
  else
    return nullptr;
}

bool ParallelEdgesConstraintCreator::canMakeConstraint(vector<ShapePart *>
                                                       *parts,
                                                       CanvasManagerState
                                                       *state) {
  if (parts->size() != 2)
    return false;

  if (state->getConstraint((*parts)[0]) != nullptr ||
      state->getConstraint((*parts)[1]) != nullptr)
    return false;

  return typeid(*(*parts)[0]) == typeid(Edge) &&
         typeid(*(*parts)[1]) == typeid(Edge);
}

bool ParallelEdgesConstraintCreator::makeConstraint(vector<ShapePart *> *parts,
                                                    CanvasManagerState *state) {
  if (!canMakeConstraint(parts, state))
    return false;

  Edge *a = dynamic_cast<Edge *>((*parts)[0]);
  Edge *b = dynamic_cast<Edge *>((*parts)[1]);

  if(a == nullptr || b == nullptr)
    return false;

  auto constraint = new ParallelEdgesConstraint(a, b);
  if (!tryToResolve(constraint, state, a, b))
    return false;

  state->addConstraint(a, constraint);
  state->addConstraint(b, constraint);
  return true;
}

bool ParallelEdgesConstraintCreator::tryToResolve(ParallelEdgesConstraint
                                                  *constraint,
                                                  CanvasManagerState
                                                  *state, Edge *a, Edge *b) {
  set<ShapePart *> s;
  auto possibleVertices = { a->getA(), a->getB(), b->getA(), b->getB() };
  for(auto possibleVertex : possibleVertices)
    if(constraint->resolveConstraint(possibleVertex, state, &s))
      return true;

  return false;
}
