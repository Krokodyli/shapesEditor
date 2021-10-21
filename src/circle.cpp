#include "circle.h"
#include "shapeAction.h"

Circle::Circle(Point pos, int r, Canvas *_canvas) : Shape(_canvas) {
  center = new CircleCenter(pos, this);
  ring = new CircleRing(r, this);
  center->setCircleRing(ring);
  ring->setCenter(center);
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
