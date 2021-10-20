#include "canvas.h"

Canvas::Canvas(Point _pos, Point _size,
               CanvasDrawManager *_canvasDrawManager)
  : pos(_pos), size(_size), canvasDrawManager(_canvasDrawManager) { }

Canvas::~Canvas() { }

void Canvas::draw(DrawManager *drawManager) {
  Point prevOffset = drawManager->getOffset();
  drawManager->setOffset(pos);

  canvasDrawManager->drawLine(Point(100, 100),
                              Point(300, 300), Color(0, 0, 0));
  canvasDrawManager->drawCircle(Point(200, 200), 100, Color(0, 0, 0));

  canvasDrawManager->display(drawManager);

  drawManager->setOffset(prevOffset);
}

void Canvas::update(CanvasManager *canvasManager, InputInfo *inputInfo) { }
