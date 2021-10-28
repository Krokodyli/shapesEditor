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

  sf::Font font;
  sf::Text textSprite;

 public:
  SFMLDrawManager(sf::RenderWindow *_window);

  virtual void loadResources();

  virtual void drawRect(int x, int y, int width, int height,
                        Color fillColor);

  virtual void drawCircle(int x, int y, int r, Color fillColor);

  virtual void drawImage(int x, int y, int imageID);

  virtual void drawSprite(sf::Sprite *sprite);

  virtual void drawText(std::string text, int x, int y, int fontSize,
                        Color color);

  virtual Point getOffset();
  virtual void setOffset(Point _offset);

  sf::Color colorToSFMLColor(Color c);
};
