#include "circleCenter.h"

CircleCenter::CircleCenter(Point _pos, Shape *_parent, CircleRing *_circleRing)
  : ShapePart(_parent), pos(_pos), circleRing(_circleRing) {}

CircleCenter::~CircleCenter() { }

CircleRing *CircleCenter::getCircleRing() { return circleRing; }

void CircleCenter::setCircleRing(CircleRing *_circleRing) {
  circleRing = _circleRing;
}

Point CircleCenter::getPos() { return pos; }

void CircleCenter::setPos(Point _pos) { pos = _pos; }

bool CircleCenter::isUnderPoint(Point p) {
  return pos.dissq(p) <= AppConsts::vertexSelectionTolerance;
}

void CircleCenter::drawOnCanvas(CanvasDrawManager *drawManager) { }

void CircleCenter::draw(DrawManager *drawManager) {
  drawManager->drawCircle(pos.x, pos.y, AppConsts::vertexSize, color);
}
