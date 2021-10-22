#pragma once

#include <string>

#include "color.h"
#include "point.h"

class DrawManager {
 public:
  virtual ~DrawManager() = 0;

  virtual void loadResources() = 0;

  virtual void drawRect(int x, int y, int width, int height,
                        Color fillColor, Color outlineColor) = 0;
  virtual void drawCircle(int x, int y, int r,
                          Color fillColor, Color outlineColor) = 0;
  virtual void drawRect(int x, int y, int width, int height,
                        Color fillColor) = 0;
  virtual void drawCircle(int x, int y, int r, Color fillColor) = 0;

  virtual void drawImage(int x, int y, int imageID) = 0;

  virtual void drawText(std::string text, int x, int y, int fontSize,
                        Color color) = 0;

  virtual Point getOffset() = 0;
  virtual void setOffset(Point offset) = 0;
};
