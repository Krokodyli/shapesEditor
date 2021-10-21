#include "color.h"

Color::Color() : Color(0, 0, 0) {}

Color::Color(unsigned int _r, unsigned int _g,
             unsigned int _b, unsigned int _a) {
  if(_r < 0 || _r > 255) _r = 0;
  if(_g < 0 || _g > 255) _g = 0;
  if (_b < 0 || _b > 255) _b = 0;
  if (_a < 0 || _a > 255) _a = 255;
  r = _r;
  g = _g;
  b = _b;
  a = _a;
}

unsigned char Color::getR() { return r; }
unsigned char Color::getG() { return g; }
unsigned char Color::getB() { return b; }
unsigned char Color::getA() { return a; }
