#include "sfmlDrawManager.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>

SFMLDrawManager::SFMLDrawManager(sf::RenderWindow *_window)
  : window(_window) { }

void SFMLDrawManager::loadResources() { }


void SFMLDrawManager::drawRect(int x, int y, int width, int height,
                               Color fillColor, Color outlineColor) {
  sf::RectangleShape rect;
  rect.setPosition(x + offset.x, y + offset.y);
  rect.setSize(sf::Vector2f(width, height));
  rect.setFillColor(colorToSFMLColor(fillColor));
  rect.setOutlineColor(colorToSFMLColor(outlineColor));
  window->draw(rect);
}

void SFMLDrawManager::drawCircle(int x, int y, int r, Color fillColor,
                                Color outlineColor) {
  sf::CircleShape circle;
  circle.setPosition(x + offset.x, y + offset.y);
  circle.setRadius(r);
  circle.setFillColor(colorToSFMLColor(fillColor));
  circle.setOutlineColor(colorToSFMLColor(outlineColor));
  window->draw(circle);
}

void SFMLDrawManager::drawRect(int x, int y, int width, int height,
                               Color fillColor) {
  sf::RectangleShape rect;
  rect.setPosition(x + offset.x, y + offset.y);
  rect.setSize(sf::Vector2f(width, height));
  rect.setFillColor(colorToSFMLColor(fillColor));
  window->draw(rect);
}

void SFMLDrawManager::drawCircle(int x, int y, int r, Color fillColor) {
  sf::CircleShape circle;
  circle.setPosition(x, y);
  circle.setRadius(r);
  circle.setFillColor(colorToSFMLColor(fillColor));
  window->draw(circle);
}

void SFMLDrawManager::drawImage(int x, int y, int imageID) { }

void SFMLDrawManager::drawSprite(sf::Sprite *sprite) {
  sf::Vector2f oldPos = sprite->getPosition();
  sprite->setPosition(oldPos.x + offset.x,
                     oldPos.y + offset.y);
  window->draw(*sprite);
  sprite->setPosition(oldPos);
}

Point SFMLDrawManager::getOffset(){ return offset; }

void SFMLDrawManager::setOffset(Point _offset) { offset = _offset; }

sf::Color SFMLDrawManager::colorToSFMLColor(Color c) {
  return sf::Color(c.getColor());
}
