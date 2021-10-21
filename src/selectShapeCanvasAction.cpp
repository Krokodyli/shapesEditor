#include "selectShapeCanvasAction.h"
#include "colorShapeAction.h"
#include <iostream>

SelectCanvasAction::SelectCanvasAction(bool _multiselectMode,
                                       bool _deselectMode,
                                       bool _coloringMode,
                                       Color _unselectedColor,
                                       Color _selectedColor)
  : multiselectMode(_multiselectMode), deselectMode(_deselectMode),
    coloringMode(_coloringMode), unselectedColor(_unselectedColor),
    selectedColor(_selectedColor) { }

void SelectCanvasAction::select(Point _p, bool _wholeShapeMode) {
  p = _p;
  wholeShapeMode = _wholeShapeMode;
  isDeselecting = false;
}

void SelectCanvasAction::deselect() {
  isDeselecting = true;
}

vector<Shape *> SelectCanvasAction::getSelectedShapes() {
  return selectedShapes;
}

vector<ShapePart *> SelectCanvasAction::getSelectedShapeParts() {
  return selectedShapesParts;
}

bool SelectCanvasAction::isSomethingSelected() {
  return (selectedShapes.size() > 0) || (selectedShapesParts.size() > 0);
}

void SelectCanvasAction::doAction(std::vector<Shape *> *shapes) {
  if(deselectMode)
    doDeselect();
  if(!isDeselecting) {
    doSelect(shapes);
  }
  else {
    doDeselect();
  }
  std::cout << selectedShapes.size() << " " << selectedShapesParts.size() << "\n";
}

bool SelectCanvasAction::canDoAction(std::vector<Shape *> *shapes) {
  return true;
}

void SelectCanvasAction::colorSelected(Shape *shape, Color c) {
  ColorShapeAction colorShapeAction(c);
  shape->doAction(&colorShapeAction);
}

void SelectCanvasAction::colorSelected(ShapePart *shapePart, Color c) {
  shapePart->setColor(c);
}

bool SelectCanvasAction::handleSelected(ShapePart *shapePart) {
  if(shapePart == nullptr)
    return false;

  if(wholeShapeMode) {
    Shape *shape = shapePart->getParent();
    if(!isAlreadySelected(shape)) {
      colorSelected(shape, selectedColor);
      selectedShapes.push_back(shape);
      return true;
    }
    else {
      return false;
    }
  }
  else {
    if(!isAlreadySelected(shapePart)) {
      colorSelected(shapePart, selectedColor);
      selectedShapesParts.push_back(shapePart);
      return true;
    }
    else {
      return false;
    }
  }
}


bool SelectCanvasAction::doSelect(std::vector<Shape *> *shapes) {
  bool selectedFlag = false;
  SelectAction selectAction(p);
  for(unsigned int i = 0; i < shapes->size(); i++) {
    auto shape = (*shapes)[i];
    shape->doAction(&selectAction);

    ShapePart *part;
    selectAction.collectResult(&part);
    selectedFlag |= handleSelected(part);
    if(selectedFlag) break;

    selectAction.resetResult();
  }
  return selectedFlag;
}

void SelectCanvasAction::doDeselect() {
  for(auto shape : selectedShapes)
    colorSelected(shape, unselectedColor);
  for(auto shapePart : selectedShapesParts)
    colorSelected(shapePart, unselectedColor);
  selectedShapes.clear();
  selectedShapesParts.clear();
}

bool SelectCanvasAction::isAlreadySelected(ShapePart *shapePart) {
  for (unsigned int i = 0; i < selectedShapesParts.size(); i++)
    if (selectedShapesParts[i] == shapePart)
      return true;
  return isAlreadySelected(shapePart->getParent());
}

bool SelectCanvasAction::isAlreadySelected(Shape * shape) {
  for (unsigned int i = 0; i < selectedShapes.size(); i++)
    if (selectedShapes[i] == shape)
      return true;
  return false;
}
