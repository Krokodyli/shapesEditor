#pragma once

#include "appConsts.h"

#include <SFML/Graphics/Texture.hpp>
#include <vector>

#include <SFML/Graphics.hpp>

using std::vector;

class SFMLResourceManager {
 private:
  vector<sf::Texture*> textures;

 public:
  ~SFMLResourceManager();

  void loadTextures();
  sf::Font loadFont();

  sf::Texture *getTexture(int imageID);
};
