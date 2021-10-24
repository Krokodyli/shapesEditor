#include "shape.h"

Shape::Shape(Canvas *_canvas) : canvas(_canvas) { }

Shape::~Shape() { }

Canvas *Shape::getCanvas() { return canvas; }
