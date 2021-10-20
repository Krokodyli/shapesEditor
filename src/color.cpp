#include "color.h"

Color::Color() : color(0) {}

Color::Color(unsigned int _color) : color(_color) {}

Color::Color(int r, int g, int b, int a) {
  if(r < 0 || r > 255) r = 0;
  if(g < 0 || g > 255) g = 0;
  if (b < 0 || b > 255) b = 0;
  if (a < 0 || a > 255) a = 255;
  color = r + 255 * (g + 255 * (b + 255 * a));
}

unsigned int Color::getColor() { return color; }
