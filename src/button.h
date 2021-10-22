#pragma once

#include <functional>

#include "drawManager.h"
#include "appConsts.h"
#include "polygon.h"

using std::function;

class InputInfo;
class CanvasManager;

class Button {
 private:
  std::string description;
  Point pos;
  int imageID;

  Color color;
  bool mouseHovering;

  function<bool(CanvasManager *)> getActiveStatusFunc;
  function<bool(CanvasManager*)> getEnabledStatusFunc;
  function<void(CanvasManager *)> actionFunc;

  Color getColor(CanvasManager *manager, InputInfo *inputInfo);
 public:
  Button(std::string _description, Point _pos, int _imageID);

  void setActionFunc(function<void(CanvasManager *)> _actionFunc);
  void setActiveStatusFunc(function<bool(CanvasManager *)> _getActiveStatusFunc);
  void setEnabledStatusFunc(function<bool(CanvasManager *)> _getEnabledStatusFunc);

  std::string getDescription();

  bool isMouseHovering();

  void draw(DrawManager *drawManager);
  void update(CanvasManager *manager, InputInfo *inputInfo);
};
