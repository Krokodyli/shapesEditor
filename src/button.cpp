#include "button.h"
#include "inputInfo.h"

Button::Button(std::string _description, Point _pos, int _imageID)
  : description(_description), pos(_pos), imageID(_imageID) { }

void Button::setActionFunc(function<void(CanvasManager *)> _actionFunc) {
  actionFunc = _actionFunc;
}

void Button::setActiveStatusFunc(function<bool(CanvasManager *)>
                                 _getActiveStatusFunc) {
  getActiveStatusFunc = _getActiveStatusFunc;
}

void Button::setEnabledStatusFunc(function<bool(CanvasManager *)>
                                  _getEnabledStatusFunc) {
  getEnabledStatusFunc = _getEnabledStatusFunc;
}

void Button::draw(DrawManager *drawManager) {
  drawManager->drawRect(pos.x, pos.y, AppConsts::buttonSize.x,
                        AppConsts::buttonSize.y, color);
  drawManager->drawImage(pos.x, pos.y, imageID);
}

void Button::update(CanvasManager *manager, InputInfo *inputInfo) {
  color = getColor(manager, inputInfo);

  if (inputInfo->getMousePos().insideRec(pos.x, pos.y,
                                         AppConsts::buttonSize.x,
                                         AppConsts::buttonSize.y))
    mouseHovering = true;

  if (actionFunc && inputInfo->isLeftClicked() && mouseHovering)
      actionFunc(manager);
}

Color Button::getColor(CanvasManager *manager, InputInfo *inputInfo) {
  if(getEnabledStatusFunc && !getEnabledStatusFunc(manager))
    return AppConsts::disabledButtonColor;
  if(getActiveStatusFunc) {
    if(getActiveStatusFunc(manager))
      return AppConsts::activeButtonColor;
    else
      return AppConsts::inactiveButtonColor;
  }
  else {
    if(inputInfo->getMousePos().insideRec(pos.x, pos.y, AppConsts::buttonSize.x,
                                          AppConsts::buttonSize.y))
      return AppConsts::activeButtonColor;
    else
      return AppConsts::inactiveButtonColor;
  }
}
