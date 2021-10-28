#include "sfmlCanvasDrawManager.h"

#include "sfmlDrawManager.h"
#include "appConsts.h"
#include <iostream>

SFMLCanvasDrawManager::SFMLCanvasDrawManager(Point _size)
  : size(_size) {
  image.create(size.x, size.y, colorToSFMLColor(AppConsts::canvasColor));
  texture.loadFromImage(image);
  sprite.setTexture(texture);
}

SFMLCanvasDrawManager::~SFMLCanvasDrawManager(){ }

void SFMLCanvasDrawManager::display(DrawManager *drawManager) {
  texture.loadFromImage(image);
  ((SFMLDrawManager*)drawManager)->drawSprite(&sprite);
  image.create(size.x, size.y, colorToSFMLColor(AppConsts::canvasColor));
}

void SFMLCanvasDrawManager::putPixel(int x, int y) {
  image.setPixel(x, y, color);
}

void SFMLCanvasDrawManager::putPixel(int x, int y, double b) {
  color.a = (int)(255 * b);
  image.setPixel(x, y, color);
}

void SFMLCanvasDrawManager::prepareColor(Color c) {
  color = colorToSFMLColor(c);
}

sf::Color SFMLCanvasDrawManager::colorToSFMLColor(Color c) {
  return sf::Color(c.getR(), c.getG(), c.getB(), c.getA());
}
