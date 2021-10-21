#include "circleRing.h"
#include "circleCenter.h"

CircleRing::CircleRing(int _r, Shape *_parent, CircleCenter *_center)
  : ShapePart(_parent), r(_r), center(_center) { }

CircleRing::~CircleRing(){ }

int CircleRing::getR() { return r; }
void CircleRing::setR(int _r) { r = _r; }
CircleCenter *CircleRing::getCenter() { return center; }
void CircleRing::setCenter(CircleCenter *_center) { center = _center; }

bool CircleRing::isUnderPoint(Point p) {
  double disp = center->getPos().dis(p);
  return disp >= r - 0.2 && disp <= r + 0.2; // TODO
}

void CircleRing::drawOnCanvas(CanvasDrawManager *drawManager) {
  drawManager->drawCircle(center->getPos(), r, color);
}

void CircleRing::draw(DrawManager *drawManager) { }
