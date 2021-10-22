#include "shapePart.h"

ShapePart::ShapePart(Shape *_parent) : parent(_parent) {
  color = AppConsts::shapeColor;
}

ShapePart::~ShapePart() { }

Shape *ShapePart::getParent() {
  return parent;
}

void ShapePart::setColor(Color _color) {
  color = _color;
}

Color ShapePart::getColor() {
  return color;
}
