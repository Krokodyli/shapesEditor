#include "circle.h"
#include "shapeAction.h"
#include "canvas.h"

Circle::Circle(Point pos, int r, Canvas *_canvas) : Shape(_canvas) {
  center = new CircleCenter(pos, this);
  ring = new CircleRing(r, this);
  center->setCircleRing(ring);
  ring->setCenter(center);
}

Circle::~Circle() {
  delete center;
  delete ring;
}

CircleCenter *Circle::getCenter() {
  return center;
}

CircleRing *Circle::getRing() {
  return ring;
}

void Circle::doAction(ShapeAction *shapeAction) {
  shapeAction->doAction(this);
}

bool Circle::canDoAction(ShapeAction *shapeAction) {
  return shapeAction->canDoAction(this);
}

void Circle::drawOnCanvas(CanvasDrawManager *drawManager) {
  ring->drawOnCanvas(drawManager);
}

void Circle::draw(DrawManager *drawManager) {
  center->draw(drawManager);
}

bool Circle::isShapeOutsideCanvas() {
  Point pos = center->getPos();
  if(!pos.insideRec(0, 0, canvas->getSize().x, canvas->getSize().y))
    return true;

  int r = ring->getR();
  if(r > pos.x || r > pos.y || r > canvas->getSize().x - 1 - pos.x
     || r > canvas->getSize().y - 1 - pos.y)
    return true;

  return false;
}
