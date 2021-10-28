#include "vertex.h"

Vertex::Vertex(Point _pos, Shape *_parent, Edge *_a, Edge *_b)
  : ShapePart(_parent), pos(_pos), a(_a), b(_b) { }

Vertex::~Vertex() { }

void Vertex::setPos(Point _pos) { pos = _pos; }

Point Vertex::getPos(){ return pos; }

void Vertex::setA(Edge *_a) { a = _a; }

void Vertex::setB(Edge *_b) { b = _b; }

Edge *Vertex::getA() { return a; }

Edge *Vertex::getB() { return b; }

Edge *Vertex::getOtherEdge(Edge *_a) {
  if(a == _a) return b;
  else if(b == _a) return a;
  else return nullptr;
}

bool Vertex::isUnderPoint(Point p) {
  return pos.dissq(p) <= AppConsts::vertexSelectionTolerance;
}

void Vertex::drawOnCanvas(CanvasDrawManager *drawManager) { }

void Vertex::draw(DrawManager *drawManager) {
  drawManager->drawCircle(pos.x, pos.y, AppConsts::vertexSize, color);
}
