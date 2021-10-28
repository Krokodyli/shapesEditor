#include "button.h"
#include "inputInfo.h"

Button::Button(std::string _description, Point _pos, int _imageID)
  : description(_description), pos(_pos), imageID(_imageID) {
  mouseHovering = false;
  getActiveStatusFunc = nullptr;
  actionFunc = nullptr;
}

void Button::setActionFunc(function<void(CanvasManager *)> _actionFunc) {
  actionFunc = _actionFunc;
}

void Button::setActiveStatusFunc(function<bool(CanvasManager *)>
                                 _getActiveStatusFunc) {
  getActiveStatusFunc = _getActiveStatusFunc;
}

std::string Button::getDescription() {
  return description;
}

bool Button::isMouseHovering() {
  return mouseHovering;
}

void Button::draw(DrawManager *drawManager) {
  drawManager->drawRect(pos.x, pos.y, AppConsts::buttonSize.x,
                        AppConsts::buttonSize.y, color);
  drawManager->drawImage(pos.x, pos.y, imageID);
}

void Button::update(CanvasManager *manager, InputInfo *inputInfo) {
  color = getColor(manager, inputInfo);

  mouseHovering = inputInfo->getMousePos().insideRec(pos.x, pos.y,
                                                     AppConsts::buttonSize.x,
                                                     AppConsts::buttonSize.y);


  if (actionFunc && inputInfo->isLeftClicked() && mouseHovering)
      actionFunc(manager);
}

Color Button::getColor(CanvasManager *manager, InputInfo *inputInfo) {
  if(getActiveStatusFunc) {
    if(getActiveStatusFunc(manager))
      return AppConsts::activeButtonColor;
    else
      return AppConsts::inactiveButtonColor;
  }
  else {
    if(mouseHovering)
      return AppConsts::activeButtonColor;
    else
      return AppConsts::inactiveButtonColor;
  }
}
