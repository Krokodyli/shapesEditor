#pragma once

#include "drawManager.h"
#include "sfmlResourceManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class SFMLDrawManager : public DrawManager {
 private:
  sf::RenderWindow *window;
  Point offset;

  SFMLResourceManager resourceManager;
  sf::Sprite sprite;

  sf::Color colorToSFMLColor(Color c);
 public:
  SFMLDrawManager(sf::RenderWindow *_window);

  virtual void loadResources();

  virtual void drawRect(int x, int y, int width, int height, Color fillColor,
                        Color outlineColor);
  virtual void drawCircle(int x, int y, int r, Color fillColor,
                          Color outlineColor);
  virtual void drawRect(int x, int y, int width, int height,
                        Color fillColor);
  virtual void drawCircle(int x, int y, int r, Color fillColor);

  virtual void drawImage(int x, int y, int imageID);

  virtual void drawSprite(sf::Sprite *sprite);

  virtual Point getOffset();
  virtual void setOffset(Point _offset);
};
