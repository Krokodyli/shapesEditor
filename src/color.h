#pragma once

class Color {
 private:
  unsigned char r, g, b, a;
 public:
  Color();
  Color(unsigned int _r, unsigned int _g,
        unsigned int _b, unsigned int _a = 255);

  unsigned char getR();
  unsigned char getG();
  unsigned char getB();
  unsigned char getA();
};
