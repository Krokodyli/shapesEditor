#include "canvas.h"

#include "polygon.h"
#include "circle.h"

Canvas::Canvas(Point _pos, Point _size, CanvasDrawManager *_canvasDrawManager)
    : pos(_pos), size(_size), canvasDrawManager(_canvasDrawManager) { }

Canvas::~Canvas() { }

void Canvas::doAction(CanvasAction *canvasAction) {
  canvasAction->doAction(&shapes);
}

bool Canvas::canDoAction(CanvasAction *canvasAction) {
  return canvasAction->canDoAction(&shapes);
}

void Canvas::draw(DrawManager *drawManager) {
  Point prevOffset = drawManager->getOffset();
  drawManager->setOffset(pos);

  for (int i = shapes.size() - 1; i >= 0; i--)
      shapes[i]->drawOnCanvas(canvasDrawManager);

  canvasDrawManager->display(drawManager);

  for(int i = shapes.size() - 1; i >= 0; i--)
    shapes[i]->draw(drawManager);

  drawManager->setOffset(prevOffset);
}

Point Canvas::getPos() { return pos; }
Point Canvas::getSize() { return size; }

Polygon *Canvas::addPolygon(vector<Point> points) {
  Polygon *pol = new Polygon(points, this);
  shapes.push_back(pol);
  return pol;
}
Circle *Canvas::addCircle(Point center, int r) {
  Circle *circle = new Circle(center, r, this);
  shapes.push_back(circle);
  return circle;
}

bool Canvas::getAntialiasingState() {
  return canvasDrawManager->getAntialiasingState();
}

void Canvas::setAntialiasingState(bool _antialiasing) {
  canvasDrawManager->setAntialiasingState(_antialiasing);
}
