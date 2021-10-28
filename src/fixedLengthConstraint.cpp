#include "fixedLengthConstraint.h"
#include "canvas.h"
#include "canvasManagerState.h"
#include "edge.h"
#include "shape.h"
#include "vertex.h"

FixedLengthConstraint::FixedLengthConstraint(Edge *_edge)
    : edge(_edge), length(edge->getA()->getPos().dis(edge->getB()->getPos())) {}

FixedLengthConstraint::~FixedLengthConstraint() { }

bool FixedLengthConstraint::isConstraintBroken() {
  return abs(edge->getLength() - length) >
    AppConsts::equalEdgesConstraintTolerance;
}

bool FixedLengthConstraint::resolveConstraint(ShapePart *p,
                                              CanvasManagerState *state,
                                              set<ShapePart *> *resolved) {
  if(!isConstraintBroken() || p == edge)
    return true;

  if(resolved->find(p) != resolved->end())
    return false;
  resolved->insert(p);

  Vertex *locked = getVertex(p);
  Vertex *other = edge->getOtherVertex(locked);

  Point prevPos = other->getPos();
  Point newPosForOther = calculateRightPosition(locked, other);

  auto canvas = p->getParent()->getCanvas();
  newPosForOther = newPosForOther.fix2Rec(Point(0,0), canvas->getSize());
  other->setPos(newPosForOther);

  Edge *otherEdge = other->getOtherEdge(edge);
  auto otherEdgeConstraint = state->getConstraint(otherEdge);
  if(otherEdgeConstraint != nullptr
     && !otherEdgeConstraint->resolveConstraint(other, state, resolved)) {
    other->setPos(prevPos);
    resolved->erase(p);
    return false;
  }

  if(!isConstraintBroken()) {
    resolved->erase(p);
    return true;
  }

  other->setPos(prevPos);
  resolved->erase(p);
  return false;
}

vector<ShapePart *> FixedLengthConstraint::getAllConstrainted() {
  return vector<ShapePart*>{ edge };
}

void FixedLengthConstraint::draw(DrawManager *drawManager, ShapePart *part) {
  Point m = (edge->getA()->getPos() + edge->getB()->getPos()) / 2;
  int size = AppConsts::constraintIconSize;
  drawManager->drawRect(m.x-size/2, m.y-size/2, size, size, color);
  drawManager->drawImage(m.x - size/2, m.y - size/2, AppConsts::lockedIconImage);
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

  if(edge == nullptr)
    return false;

  state->addConstraint(edge, new FixedLengthConstraint(edge));

  return true;
}
