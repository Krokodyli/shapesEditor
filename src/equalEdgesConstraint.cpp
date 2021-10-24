#include "equalEdgesConstraint.h"
#include "canvasManagerState.h"
#include "edge.h"
#include "shapePart.h"
#include "vertex.h"
#include "shape.h"
#include "canvas.h"

EqualEdgesConstraint::EqualEdgesConstraint(Edge *_a, Edge *_b)
  : a(_a), b(_b) { }

EqualEdgesConstraint::~EqualEdgesConstraint() { }

bool EqualEdgesConstraint::isConstraintBroken() {
  return abs(a->getLength()-b->getLength()) > 4;
}

bool EqualEdgesConstraint::resolveConstraint(ShapePart *p,
                                             CanvasManagerState *state,
                                             set<ShapePart *> *resolved) {
  if (!isConstraintBroken())
    return true;

  if (resolved->find(p) != resolved->end())
    return false;
  resolved->insert(p);

  Edge *edge = getEdgeFromVertex(p);
  Edge *otherEdge = getOtherEdge(edge);

  if(resolveWithVertex(otherEdge, edge->getLength(),
                       otherEdge->getA(), state, resolved)) {
    resolved->erase(p);
    return true;
  }

  if (resolveWithVertex(otherEdge, edge->getLength(), otherEdge->getB(), state,
                        resolved)) {
    resolved->erase(p);
    return true;
  }

  resolved->erase(p);
  return false;
}

vector<ShapePart *> EqualEdgesConstraint::getAllConstrainted() {
  return vector<ShapePart*> { a, b };
};

void EqualEdgesConstraint::draw(DrawManager *drawManager, ShapePart *part) {
  if(part == a) {
    Point m = (a->getA()->getPos() + a->getB()->getPos()) / 2;
    drawManager->drawRect(m.x - 12, m.y - 12, 25, 25, Color(255, 0, 0));
  }
  if (part == b) {
    Point m = (b->getA()->getPos() + b->getB()->getPos()) / 2;
    drawManager->drawRect(m.x - 12, m.y - 12, 25, 25, Color(255, 0, 0));
  }
}

Edge *EqualEdgesConstraint::getEdgeFromVertex(ShapePart *part) {
  if(part == a->getA() || part == a->getB())
    return a;
  else if(part == b->getA() || part == b->getB())
    return b;
  else
    return nullptr;
}

Edge *EqualEdgesConstraint::getOtherEdge(Edge *e) {
  if(e == a)
    return b;
  else if(e == b)
    return a;
  else
    return nullptr;
}

bool EqualEdgesConstraint::resolveWithVertex(Edge *edge, double expLen,
                                             Vertex *v,
                                             CanvasManagerState *state,
                                             set<ShapePart*> *resolved) {
  if(resolved->find(v) != resolved->end())
    return false;
  resolved->insert(v);

  Vertex *other = edge->getOtherVertex(v);

  Point prevPos = other->getPos();
  Point newPosForOther = calculateRightPosition(v, other, expLen);
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

Point EqualEdgesConstraint::calculateRightPosition(Vertex *locked,
                                                   Vertex *vertex,
                                                   double expLen) {
  double c = expLen / locked->getPos().dis(vertex->getPos());

  Point p = vertex->getPos();
  Point l = locked->getPos();

  p.x = l.x + c * ((double)p.x - (double)l.x);
  p.y = l.y + c * ((double)p.y - (double)l.y);

  return p;
}

bool EqualEdgesConstraintCreator::canMakeConstraint(vector<ShapePart *> *parts,
                                                     CanvasManagerState *state) {
  if(parts->size() != 2)
    return false;

  if(state->getConstraint((*parts)[0]) != nullptr
     || state->getConstraint((*parts)[1]) != nullptr)
     return false;

  return typeid(*(*parts)[0]) == typeid(Edge)
    && typeid(*(*parts)[1]) == typeid(Edge);
}

bool EqualEdgesConstraintCreator::makeConstraint(vector<ShapePart *> *parts,
                                                  CanvasManagerState *state) {
  if(!canMakeConstraint(parts, state))
    return false;

  Edge *a = dynamic_cast<Edge*>((*parts)[0]);
  Edge *b = dynamic_cast<Edge *>((*parts)[1]);

  if(a != nullptr && b != nullptr) {
    auto constraint = new EqualEdgesConstraint(a, b);
    if(!tryToResolve(constraint, state, a, b))
      return false;

    state->addConstraint(a, constraint);
    state->addConstraint(b, constraint);
    return true;
  }
  else {
    return false;
  }
}

bool EqualEdgesConstraintCreator::tryToResolve(EqualEdgesConstraint *constraint,
                                               CanvasManagerState *state,
                                               Edge *a, Edge *b) {
  set<ShapePart*> s;
  if(constraint->resolveConstraint(a->getA(), state, &s))
    return true;
  if (constraint->resolveConstraint(a->getB(), state, &s))
    return true;
  if (constraint->resolveConstraint(b->getA(), state, &s))
    return true;
  if (constraint->resolveConstraint(b->getB(), state, &s))
    return true;
  return false;
}
