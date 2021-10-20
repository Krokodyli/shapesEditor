#pragma once

#include "color.h"
#include "drawManager.h"

class CanvasDrawManager {
 protected:
  virtual void drawCirclePoints(int xc, int yc, int x, int y);
  virtual void putPixel(int x, int y) = 0;
  virtual void prepareColor(Color c) = 0;
 public:
  virtual ~CanvasDrawManager();

  virtual void drawLine(Point a, Point b, Color color);
  virtual void drawCircle(Point c, int r, Color color);

  virtual void display(DrawManager *drawManager) = 0;
};
