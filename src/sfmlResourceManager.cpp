#include "sfmlResourceManager.h"

SFMLResourceManager::~SFMLResourceManager() {
  for(auto texture : textures)
    delete texture;
}

void SFMLResourceManager::loadTextures() {
  for(auto path : AppConsts::imagesPaths) {
    sf::Texture *newTexture = new sf::Texture();
    newTexture->loadFromFile(AppConsts::getResourcePath(path));
    textures.push_back(newTexture);
  }
}

sf::Font SFMLResourceManager::loadFont() {
  sf::Font font;
  font.loadFromFile(AppConsts::getResourcePath(AppConsts::fontPath));
  return font;
}

sf::Texture *SFMLResourceManager::getTexture(int imageID) {
  if(imageID < 0 || imageID > (int)textures.size())
    return nullptr;
  else
    return textures[imageID];
}
