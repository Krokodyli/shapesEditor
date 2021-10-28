#include "tangentConstraint.h"
#include "circleCenter.h"
#include "circleRing.h"
#include "canvas.h"
#include "shapePart.h"

TangentConstraint::TangentConstraint(Edge *_a, Circle *_c)
  : a(_a), c(_c), p(c->getCenter()), r(c->getRing()) { }

TangentConstraint::~TangentConstraint() { }

bool TangentConstraint::isConstraintBroken() {
  Point m = (a->getA()->getPos() + a->getB()->getPos()) / 2;
  return abs(m.dis(p->getPos())-r->getR()) > 1;
}

bool TangentConstraint::resolveIfCircleMoved(CanvasManagerState *state,
                                       set<ShapePart *> *resolved) {
  if(!isConstraintBroken())
    return true;

  Point prevAPos = a->getA()->getPos(), prevBPos = a->getB()->getPos();
  Point m = (a->getA()->getPos() + a->getB()->getPos()) / 2;
  m = p->getPos() + (m - p->getPos()) * ((double)r->getR()/m.dis(p->getPos()));
  auto possiblePositions = getPerpendicularPoint(m, p->getPos(),
                                                 a->getLength()/2);

  if(possiblePositions.first.dis(a->getA()->getPos()) >
     possiblePositions.second.dis(a->getA()->getPos())) {
    Point tmp = possiblePositions.first;
    possiblePositions.first = possiblePositions.second;
    possiblePositions.second = tmp;
  }

  a->getA()->setPos(possiblePositions.first);
  a->getB()->setPos(possiblePositions.second);

  resolved->insert(a->getB());
  auto constraint = state->getConstraint(a->getA()->getOtherEdge(a));
  if(constraint != nullptr
     && !constraint->resolveConstraint(a->getA(), state, resolved)) {
    a->getA()->setPos(prevAPos);
    a->getB()->setPos(prevBPos);
    resolved->erase(a->getB());
    return false;
  }
  resolved->erase(a->getB());

  resolved->insert(a->getA());
  constraint = state->getConstraint(a->getB()->getOtherEdge(a));
  if(constraint != nullptr
     && !constraint->resolveConstraint(a->getB(), state, resolved)) {
    a->getA()->setPos(prevAPos);
    a->getB()->setPos(prevBPos);
    resolved->erase(a->getA());
    return false;
  }
  resolved->erase(a->getA());

  return true;
}

bool TangentConstraint::resolveIfEdgeMoved(CanvasManagerState *state,
                                         set<ShapePart *> *resolved) {
  if (!isConstraintBroken())
    return true;

  Point m = (a->getA()->getPos() + a->getB()->getPos()) / 2;
  auto possiblePositions = getPerpendicularPoint(m, a->getA()->getPos(),
                                                 r->getR());
  Point newPos = possiblePositions.first;
  Point altPos = possiblePositions.second;

  swapPositionsToPreferredOrder(newPos, altPos);

  if (isMovedCircleInsideCanvas(newPos)) {
    p->setPos(newPos);
    return true;
  }
  else if(isMovedCircleInsideCanvas(altPos)) {
    p->setPos(altPos);
    return true;
  }
  else {
    return false;
  }
}

std::pair<Point, Point> TangentConstraint::getPerpendicularPoint(Point m,
                                                                 Point b,
                                                                 double len) {
  Point delta = b - m;
  Point dm1 = Point(delta.y, -delta.x);
  Point dm2 = Point(-delta.y, delta.x);
  dm1 = dm1 * (len / dm1.dis(Point(0, 0)));
  dm2 = dm2 * (len / dm2.dis(Point(0, 0)));
  return std::make_pair(m + dm1, m + dm2);
}

bool TangentConstraint::isMovedCircleInsideCanvas(Point newCenterPos) {
  Point canvasSize = c->getCanvas()->getSize();
  return (newCenterPos.insideRec(0, 0, canvasSize.x, canvasSize.y) &&
          newCenterPos.x >= r->getR() && newCenterPos.y >= r->getR() &&
          canvasSize.x - 1 - newCenterPos.x >= r->getR() &&
          canvasSize.y - 1 - newCenterPos.y >= r->getR());
}

void TangentConstraint::swapPositionsToPreferredOrder(Point &newPos,
                                                      Point &altPos) {
  if(p->getPos().dis(newPos) > p->getPos().dis(altPos)) {
    Point tmp = newPos;
    newPos = altPos;
    altPos = tmp;
  }
}

bool TangentConstraint::resolveConstraint(ShapePart *part, CanvasManagerState *state,
                                          set<ShapePart *> *resolved) {
  if(!isConstraintBroken())
    return true;

  if(resolved->find(part) != resolved->end())
    return false;
  resolved->insert(p);

  if(part == a->getA() || part == a->getB() || part == a) {
    bool ret = resolveIfEdgeMoved(state, resolved);
    resolved->erase(p);
    return ret;
  }
  else if(part == p || part == r) {
    bool ret = resolveIfCircleMoved(state, resolved);
    resolved->erase(p);
    return ret;
  }
  return false;
}

vector<ShapePart *> TangentConstraint::getAllConstrainted() {
  return { p, r, a };
}

void TangentConstraint::draw(DrawManager *drawManager, ShapePart *part) {
  if(part == r) {
    Point pos = r->getCenter()->getPos();
    pos.y -= r->getR();
    pos.y -= 12;
    drawManager->drawRect(pos.x, pos.y, 25, 25, color);
    drawManager->drawImage(pos.x, pos.y, AppConsts::lockedIconImage);
  }
}

bool TangentConstraintCreator::canMakeConstraint(vector<ShapePart *> *parts,
                                                 CanvasManagerState *state) {
  if(parts->size() != 2)
    return false;

  if(state->getConstraint((*parts)[0]) != nullptr
     || state->getConstraint((*parts)[1]) != nullptr)
    return false;

  if(typeid(*(*parts)[0]) != typeid(Edge)
     && typeid(*(*parts)[1]) != typeid(Edge))
     return false;

  if(typeid(*(*parts)[0]) != typeid(CircleRing)
     && typeid(*(*parts)[1]) != typeid(CircleRing)
     && typeid(*(*parts)[0]) != typeid(CircleCenter)
     && typeid(*(*parts)[1]) != typeid(CircleCenter))
     return false;

  return true;
}

bool TangentConstraintCreator::makeConstraint(vector<ShapePart *> *parts,
                                              CanvasManagerState *state) {
  if(!canMakeConstraint(parts, state))
    return false;

  Edge *e = getEdge(parts);
  Circle *circle = nullptr;

  CircleCenter *c = getCenter(parts);
  if(c != nullptr) {
    circle = dynamic_cast<Circle*>(c->getParent());
  }
  else {
    CircleRing *r = getRing(parts);
    if(r != nullptr)
      circle = dynamic_cast<Circle*>(r->getParent());
  }

  auto constraint = new TangentConstraint(e, circle);
  if(!tryToResolve(constraint, state, e, circle))
    return false;

  for(auto shapePart : constraint->getAllConstrainted())
    state->addConstraint(shapePart, constraint);

  return true;
}

Edge *TangentConstraintCreator::getEdge(vector<ShapePart *> *parts) {
  Edge *e;
  for (int i = 0; i <= 1; i++) {
    e = dynamic_cast<Edge *>((*parts)[i]);
    if (e != nullptr)
      return e;
  }
  return nullptr;
}

CircleRing *TangentConstraintCreator::getRing(vector<ShapePart *> *parts) {
  CircleRing *r;
  for (int i = 0; i <= 1; i++) {
    r = dynamic_cast<CircleRing *>((*parts)[i]);
    if (r != nullptr)
      return r;
  }
  return nullptr;
}

CircleCenter *TangentConstraintCreator::getCenter(vector<ShapePart *> *parts) {
  CircleCenter *c;
  for(int i = 0; i <= 1; i++) {
    c = dynamic_cast<CircleCenter *>((*parts)[i]);
    if (c != nullptr)
      return c;
  }
  return nullptr;
}

bool TangentConstraintCreator::tryToResolve(TangentConstraint *constraint,
                                            CanvasManagerState *state,
                                            Edge *a, Circle *c) {
  set<ShapePart*> s;
  if(!constraint->resolveConstraint(a->getA(), state, &s))
    return true;
  return true;
}
