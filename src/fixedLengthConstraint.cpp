#include "fixedLengthConstraint.h"
#include "canvas.h"
#include "canvasManagerState.h"
#include "edge.h"
#include "shape.h"
#include "vertex.h"
#include <iostream>

FixedLengthConstraint::FixedLengthConstraint(Edge *_edge)
    : edge(_edge), length(edge->getA()->getPos().dis(edge->getB()->getPos())) {}

FixedLengthConstraint::~FixedLengthConstraint() { }

bool FixedLengthConstraint::isConstraintBroken() {
  double dis = edge->getA()->getPos().dis(edge->getB()->getPos());
  return abs(dis - length) > 4;
}

bool FixedLengthConstraint::resolveConstraint(ShapePart *p,
                                              CanvasManagerState *state,
                                              set<ShapePart *> resolved) {
  if(!isConstraintBroken())
    return true;

  if(resolved.find(p) != resolved.end())
    return false;
  resolved.insert(p);

  Vertex *locked = getVertex(p);
  Vertex *other = edge->getOtherVertex(locked);

  Point prevPos = other->getPos();
  Point newPosForOther = calculateRightPosition(locked, other);
  newPosForOther = newPosForOther.fix2Rec(Point(0,0),
                                          p->getParent()->getCanvas()->getSize());
  other->setPos(newPosForOther);

  Edge *otherEdge = other->getOtherEdge(edge);
  auto otherEdgeConstraint = state->getConstraint(otherEdge);
  if(otherEdgeConstraint != nullptr
     && !otherEdgeConstraint->resolveConstraint(other, state, resolved)) {
    other->setPos(prevPos);
    resolved.erase(p);
    return false;
  }

  if(!isConstraintBroken()) {
    resolved.erase(p);
    return true;
  }

  other->setPos(prevPos);
  resolved.erase(p);
  return false;
}

vector<ShapePart *> FixedLengthConstraint::getAllConstrainted() {
  return vector<ShapePart*>{ edge };
}

void FixedLengthConstraint::draw(DrawManager *drawManager) {
  Point m = (edge->getA()->getPos() + edge->getB()->getPos()) / 2;
  drawManager->drawRect(m.x-12, m.y-12, 25, 25, Color(255, 0, 0));
}

Vertex *FixedLengthConstraint::getVertex(ShapePart *part) {
  if(edge->getA() == part)
    return edge->getA();
  else if(edge->getB() == part)
    return edge->getB();
  return nullptr;
}

Point FixedLengthConstraint::calculateRightPosition(Vertex *locked,
                                                    Vertex *vertex) {
  double c = length/locked->getPos().dis(vertex->getPos());

  Point p = vertex->getPos();
  Point l = locked->getPos();

  p.x = l.x + c * ((double)p.x - (double)l.x);
  p.y = l.y + c * ((double)p.y - (double)l.y);

  return p;
}

bool FixedLengthConstraintCreator::canMakeConstraint(vector<ShapePart *> *parts,
                                                     CanvasManagerState *state) {
  if(parts->size() != 1)
    return false;

  if(state->getConstraint((*parts)[0]) != nullptr)
    return false;

  return typeid(*(*parts)[0]) == typeid(Edge);
}

bool FixedLengthConstraintCreator::makeConstraint(vector<ShapePart *> *parts,
                                                  CanvasManagerState *state) {
  if(!canMakeConstraint(parts, state))
    return false;

  Edge *edge = dynamic_cast<Edge*>((*parts)[0]);

  if(edge != nullptr) {
    state->addConstraint(edge, new FixedLengthConstraint(edge));
    return true;
  }
  else {
    return false;
  }
}