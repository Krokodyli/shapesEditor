#include "constructManagerMode.h"

ConstructManagerMode::ConstructManagerMode(createConstructionFunc
                                           _createShapeFunc,
                                           Canvas *canvas)
  : createShapeFunc(_createShapeFunc),
    constructAction(createShapeFunc, canvas) { }

void ConstructManagerMode::start(Canvas *canvas) { }

void ConstructManagerMode::update(Canvas *canvas, InputInfo *inputInfo) {
  auto mousePos = inputInfo->getMousePos();
  auto oldMousePos = inputInfo->getPrevMousePos();

  if(inputInfo->isLeftClicked())
    constructAction.putConstructionPoint();
  else if(mousePos != oldMousePos)
    constructAction.moveConstructionPoint(mousePos.fix2Rec(Point(0, 0),
                                                           canvas->getSize()));

  canvas->doAction(&constructAction);
}

void ConstructManagerMode::stop(Canvas *canvas) {
  constructAction.cleanUp();
  canvas->doAction(&constructAction);
}
