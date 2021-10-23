#include "constructionPolygon.h"
#include "polygon.h"
#include <iostream>

ConstructionPolygon::ConstructionPolygon(Canvas *_canvas)
  : ConstructionShape(_canvas), shouldFinish(false) { }

ConstructionPolygon::~ConstructionPolygon() { }

void ConstructionPolygon::start(Point pos) {
  shouldFinish = false;
  points.push_back(pos);
}

void ConstructionPolygon::moveConstructionPoint(Point newPos) {
  if(points.size() > 0)
    points[points.size()-1] = newPos;
}

void ConstructionPolygon::putConstructionPoint() {
  int n = points.size();
  if (points.size() > 3 && points[n - 1].dissq(points[0]) <=
      AppConsts::vertexSelectionTolerance) {
    shouldFinish = true;
    points.pop_back();
  }
  else if (n > 0) {
    points.push_back(points[n - 1]);
  }
}

bool ConstructionPolygon::canFinishConstruction() {
  return shouldFinish;
}

Shape *ConstructionPolygon::finishShapeConstruction() {
  if(!canFinishConstruction())
    return nullptr;

  auto polygon = new Polygon(points, canvas);

  points.clear();
  shouldFinish = false;

  return polygon;
}

void ConstructionPolygon::doAction(ShapeAction *shapeAction) { }

bool ConstructionPolygon::canDoAction(ShapeAction *shapeAction) {
  return false;
}

void ConstructionPolygon::drawOnCanvas(CanvasDrawManager *drawManager) {
  if(points.size() > 1) {
    for(unsigned int i = 0; i < points.size() - 1; i++) {
      auto a = points[i], b = points[i+1];
      drawManager->drawLine(a, b, AppConsts::shapeColor);
    }
  }
}

void ConstructionPolygon::draw(DrawManager *drawManager) {
  for(auto v : points)
    drawManager->drawCircle(v.x, v.y, AppConsts::vertexSize,
                            AppConsts::shapeColor);
}

bool ConstructionPolygon::isShapeOutsideCanvas() {
  return false;
}
