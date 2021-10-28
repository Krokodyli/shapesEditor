#include "selectAction.h"

#include "circle.h"
#include "polygon.h"

SelectAction::SelectAction(Point _p)
  : p(_p), selShapePart(nullptr) { }

void SelectAction::collectResult(ShapePart **_selShapePart) {
  *_selShapePart = selShapePart;
}

void SelectAction::resetResult() {
  selShapePart = nullptr;
}

void SelectAction::doAction(Circle *circle) {
  if (circle->getRing()->isUnderPoint(p))
    selShapePart = (ShapePart *)circle->getRing();
  else if (circle->getCenter()->isUnderPoint(p))
    selShapePart = (ShapePart *)circle->getCenter();
}

void SelectAction::doAction(Polygon *polygon) {
  polygon->map2Vertices([&, this](Vertex *v) {
    if(this->selShapePart == nullptr && v->isUnderPoint(p))
      this->selShapePart = v;
  });

  if(selShapePart != nullptr)
    return;

  polygon->map2Edges([&, this](Edge *e) {
    if (this->selShapePart == nullptr && e->isUnderPoint(p))
      this->selShapePart = e;
  });
}

bool SelectAction::canDoAction(Circle *circle) {
  return true;
}

bool SelectAction::canDoAction(Polygon *polygon) {
  return true;
}
