#pragma once

#include "app.h"

#include "SFML/Graphics.hpp"

class SFMLApp : public App {
protected:
  sf::RenderWindow *window;

  virtual void setup();
  virtual void draw();
  virtual void handleEvents();
public:
  virtual ~SFMLApp();
};
