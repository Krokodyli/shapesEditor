#pragma once

#include "app.h"

#include "SFML/Graphics.hpp"

class SFMLApp : public App {
protected:
  sf::RenderWindow *window;

  sf::Clock clock;
  sf::Clock showFPSClock;
  int fps;
  bool showFPS = false;

  virtual void setup();
  virtual void draw();
  virtual void handleEvents();
public:
  SFMLApp(Point _size);
  virtual ~SFMLApp();
};
