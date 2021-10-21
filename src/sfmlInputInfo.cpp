#include "sfmlInputInfo.h"

SFMLInputInfo::SFMLInputInfo(sf::Window *_window) : window(_window) { }

SFMLInputInfo::~SFMLInputInfo() {}

void SFMLInputInfo::update() {
  _wasLeftPressed = _isLeftPressed;
  _wasRightPressed = _isRightPressed;
  oldMousePos = mousePos;

  _isLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
  _isRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
  auto sfmlMousePos = sf::Mouse::getPosition(*window);
  mousePos.x = sfmlMousePos.x;
  mousePos.y = sfmlMousePos.y;
}

bool SFMLInputInfo::isLeftPressed() { return _isLeftPressed; }
bool SFMLInputInfo::isRightPressed() { return _isRightPressed; }
bool SFMLInputInfo::wasLeftPressed() { return _wasLeftPressed; }
bool SFMLInputInfo::wasRightPressed() { return _wasRightPressed; }

bool SFMLInputInfo::isLeftClicked() {
  return _isLeftPressed && !_wasLeftPressed;
}

bool SFMLInputInfo::isRightClicked() {
  return _isRightPressed && !_wasRightPressed;
}

Point SFMLInputInfo::getMousePos() { return mousePos - offset; }

Point SFMLInputInfo::getPrevMousePos() { return oldMousePos - offset; }

Point SFMLInputInfo::getOffset() {
  return offset;
}

void SFMLInputInfo::setOffset(Point _offset) {
  offset = _offset;
}
