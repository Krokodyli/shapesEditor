#pragma once

#include "inputInfo.h"

#include <chrono>

#include <SFML/Window.hpp>

class SFMLInputInfo : public InputInfo {
 private:
  sf::Window *window;
  Point offset;

  bool _isLeftPressed, _wasLeftPressed;
  bool _isRightPressed, _wasRightPressed;
  Point mousePos, oldMousePos;

  int prevLeftClickTime, leftClickTime;

  int getMilisecondsFromEpoch();
public:
  SFMLInputInfo(sf::Window *_window);
  virtual ~SFMLInputInfo();

  virtual void update();

  virtual bool isLeftPressed();
  virtual bool isRightPressed();
  virtual bool wasLeftPressed();
  virtual bool wasRightPressed();
  virtual bool isLeftClicked();
  virtual bool isRightClicked();

  virtual bool wasLeftClickDouble(int gapInMiliseconds);

  virtual Point getMousePos();
  virtual Point getPrevMousePos();

  virtual Point getOffset();
  virtual void setOffset(Point _offset);
};
