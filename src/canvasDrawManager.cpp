#include "canvasDrawManager.h"

CanvasDrawManager::~CanvasDrawManager() { }

void CanvasDrawManager::drawLine(Point a, Point b, Color color) {
  prepareColor(color);
  int d, dx, dy, ai, bi, xi, yi;
  int x = a.x, y = a.y;
  // ustalenie kierunku rysowania
  if (a.x < b.x)
  {
      xi = 1;
      dx = b.x - a.x;
  }
  else
  {
      xi = -1;
      dx = a.x - b.x;
  }
  // ustalenie kierunku rysowania
  if (a.y < b.y)
  {
      yi = 1;
      dy = b.y - a.y;
  }
  else
  {
      yi = -1;
      dy = a.y - b.y;
  }
  // pierwszy piksel
  putPixel(x, y);
  // oś wiodąca OX
  if (dx > dy)
  {
      ai = (dy - dx) * 2;
      bi = dy * 2;
      d = bi - dx;
      // pętla po kolejnych x
      while (x != b.x)
      {
          // test współczynnika
          if (d >= 0)
          {
              x += xi;
              y += yi;
              d += ai;
          }
          else
          {
              d += bi;
              x += xi;
          }
          putPixel(x, y);
      }
  }
  // oś wiodąca OY
  else
  {
      ai = ( dx - dy ) * 2;
      bi = dx * 2;
      d = bi - dy;
      // pętla po kolejnych y
      while (y != b.y)
      {
          // test współczynnika
          if (d >= 0)
          {
              x += xi;
              y += yi;
              d += ai;
          }
          else
          {
              d += bi;
              y += yi;
          }
          putPixel(x, y);
      }
  }
}

void CanvasDrawManager::drawCircle(Point c,  int r, Color color){
  if(r == 0) return;
  int x = 0, y = r;
  int param = 3 - 2 * r;
  drawCirclePoints(c.x, c.y, x, y);
  while(y >= x) {
    x++;
    if(param > 0) {
      y--;
      param = param + 4 * (x - y) + 10;
    }
    else {
      param = param + 4 * x + 6;
    }
    drawCirclePoints(c.x, c.y, x, y);
  }
}

void CanvasDrawManager::drawCirclePoints(int xc, int yc, int x, int y) {
  putPixel(xc + x, yc + y);
  putPixel(xc - x, yc + y);
  putPixel(xc + x, yc - y);
  putPixel(xc - x, yc - y);

  putPixel(xc + y, yc + x);
  putPixel(xc - y, yc + x);
  putPixel(xc + y, yc - x);
  putPixel(xc - y, yc - x);
}
