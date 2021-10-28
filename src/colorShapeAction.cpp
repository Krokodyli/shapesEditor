#include "colorShapeAction.h"
#include "polygon.h"
#include "circle.h"

ColorShapeAction::ColorShapeAction(Color _color) : color(_color) { }

void ColorShapeAction::doAction(Circle *circle) {
  circle->getCenter()->setColor(color);
  circle->getRing()->setColor(color);
}

void ColorShapeAction::doAction(Polygon *polygon) {
  polygon->map2Vertices([this](Vertex *v){
    v->setColor(color);
  });
  polygon->map2Edges([this](Edge *e) {
    e->setColor(color);
  });
}

bool ColorShapeAction::canDoAction(Circle *circle) {
  return true;
}

bool ColorShapeAction::canDoAction(Polygon *polygon) {
  return true;
}
