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

void Canvas::draw(DrawManager *drawManager) {
  Point prevOffset = drawManager->getOffset();
  drawManager->setOffset(pos);

  for(auto shape : shapes)
    shape->drawOnCanvas(canvasDrawManager);

  canvasDrawManager->display(drawManager);

  for (auto shape : shapes)
    shape->draw(drawManager);

  drawManager->setOffset(prevOffset);
}

void Canvas::update(CanvasManager *canvasManager, InputInfo *inputInfo) { }
