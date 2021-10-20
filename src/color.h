#pragma once

class Color {
 private:
  unsigned int color;
 public:
  Color();
  Color(unsigned int _color);
  Color(int r, int g, int b, int a = 255);
  unsigned int getColor();
};