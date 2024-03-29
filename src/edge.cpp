#include "edge.h"
#include "vertex.h"

Edge::Edge(Shape *_parent, Vertex *_a, Vertex *_b)
    : ShapePart(_parent), a(_a), b(_b) {}

Edge::~Edge() { }

void Edge::setA(Vertex *_a) { a = _a; }
void Edge::setB(Vertex *_b) { b = _b; }
Vertex *Edge::getA(){ return a; }
Vertex *Edge::getB() { return b; }

Vertex *Edge::getOtherVertex(Vertex *_a) {
  if(a == _a) return b;
  else if(b == _a) return a;
  else return nullptr;
}

double Edge::getLength() {
  return a->getPos().dis(b->getPos());
}

double Edge::getLeanRatio() {
  double dx;

  if(a->getPos().y >= b->getPos().y)
    dx = a->getPos().x - b->getPos().x;
  else
    dx = b->getPos().x - a->getPos().x;

  return acos(dx/getLength());
}

bool Edge::isUnderPoint(Point p) {
  return p.dis(a->getPos()) + p.dis(b->getPos())
    <= a->getPos().dis(b->getPos()) + AppConsts::edgeSelectionTolerance;
}

void Edge::drawOnCanvas(CanvasDrawManager *drawManager) {
  drawManager->drawLine(a->getPos(), b->getPos(), color);
}

void Edge::draw(DrawManager *drawManager) { }
