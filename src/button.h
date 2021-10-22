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
  Point pos;
  int imageID;

  Color color;

  function<bool(CanvasManager *)> getActiveStatusFunc;
  function<bool(CanvasManager*)> getEnabledStatusFunc;
  function<void(CanvasManager *)> actionFunc;

  Color getColor(CanvasManager *manager, InputInfo *inputInfo);
 public:
  Button(Point _pos, int _imageID);

  void setActionFunc(function<void(CanvasManager *)> _actionFunc);
  void setActiveStatusFunc(function<bool(CanvasManager *)> _getActiveStatusFunc);
  void setEnabledStatusFunc(function<bool(CanvasManager *)> _getEnabledStatusFunc);

  void draw(DrawManager *drawManager);
  void update(CanvasManager *manager, InputInfo *inputInfo);
};
