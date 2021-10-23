#include "constructionCircle.h"
#include "canvas.h"
#include "circle.h"
#include <iostream>

ConstructionCircle::ConstructionCircle(Canvas *_canvas)
  : ConstructionShape(_canvas), isCenterPut(false), isRingPut(false) { }

ConstructionCircle::~ConstructionCircle() {}

void ConstructionCircle::start(Point pos) {
  isCenterPut = false;
  isRingPut = false;
  center = pos;
}

void ConstructionCircle::moveConstructionPoint(Point newPos) {
  if(!isCenterPut) {
    center = newPos;
  }
  if(!isRingPut) {
    radius = center.dis(newPos);
    radius = std::min(radius, center.x);
    radius = std::min(radius, center.y);
    radius = std::min(radius, canvas->getSize().x - 1 - center.x);
    radius = std::min(radius, canvas->getSize().y - 1 - center.y);
  }
}

void ConstructionCircle::putConstructionPoint() {
  if(!isCenterPut) {
    isCenterPut = true;
    radius = 0;
  }
  else if(!isRingPut) {
    isRingPut = true;
  }
}

bool ConstructionCircle::canFinishConstruction() {
  return isCenterPut && isRingPut;
}

Shape *ConstructionCircle::finishShapeConstruction() {
  if(!canFinishConstruction())
    return nullptr;

  auto circle = new Circle(center, radius, canvas);
  isCenterPut = false;
  isRingPut = false;

  return circle;
}

void ConstructionCircle::doAction(ShapeAction *shapeAction) { }
bool ConstructionCircle::canDoAction(ShapeAction *shapeAction){ return false; }

void ConstructionCircle::drawOnCanvas(CanvasDrawManager *drawManager) {
  if(isCenterPut) {
    drawManager->drawCircle(center, radius, AppConsts::shapeColor);
  }
}

void ConstructionCircle::draw(DrawManager *drawManager) {
  drawManager->drawCircle(center.x, center.y, AppConsts::vertexSize,
                          AppConsts::shapeColor);
}

bool ConstructionCircle::isShapeOutsideCanvas() {
  return false;
}
