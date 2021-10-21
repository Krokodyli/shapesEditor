#include "canvas.h"

#include "polygon.h"
#include "circle.h"

Canvas::Canvas(Point _pos, Point _size,
               CanvasDrawManager *_canvasDrawManager)
  : pos(_pos), size(_size), canvasDrawManager(_canvasDrawManager) {
  shapes.push_back(new Polygon(vector<Point>{
        Point(100, 100),
        Point(300, 100),
        Point(200, 300)
      }, this));
  shapes.push_back(new Polygon(vector<Point>{
        Point(500, 500),
        Point(500, 100),
        Point(600, 20),
        Point(700, 500)}, this));
  shapes.push_back(new Circle(Point(500, 500), 50, this));
  shapes.push_back(new Circle(Point(320, 150), 20, this));
  shapes.push_back(new Circle(Point(120, 120), 120, this));
}

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
