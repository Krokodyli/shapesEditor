#include "sfmlInputInfo.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

SFMLInputInfo::SFMLInputInfo(sf::Window *_window) : window(_window) {
  prevLeftClickTime = -1000000;
  leftClickTime = 0;
}

SFMLInputInfo::~SFMLInputInfo() { }

void SFMLInputInfo::update() {
  _wasLeftPressed = _isLeftPressed;
  _wasRightPressed = _isRightPressed;
  oldMousePos = mousePos;

  _isLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
  if(isLeftClicked()) {
    prevLeftClickTime = leftClickTime;
    leftClickTime = getMilisecondsFromEpoch();
  }

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

bool SFMLInputInfo::wasLeftClickDouble(int gapInMiliseconds) {
  return leftClickTime - prevLeftClickTime <= gapInMiliseconds;
}

Point SFMLInputInfo::getMousePos() { return mousePos - offset; }

Point SFMLInputInfo::getPrevMousePos() { return oldMousePos - offset; }

Point SFMLInputInfo::getOffset() {
  return offset;
}

void SFMLInputInfo::setOffset(Point _offset) {
  offset = _offset;
}

int SFMLInputInfo::getMilisecondsFromEpoch() {
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
      .count();
}
