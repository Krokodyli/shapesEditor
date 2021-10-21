#include "shapePart.h"

ShapePart::ShapePart(Shape *_parent) : parent(_parent) {
  color = Color(0, 0, 0); // TODO
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
