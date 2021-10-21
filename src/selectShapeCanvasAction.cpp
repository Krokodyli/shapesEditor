#include "selectShapeCanvasAction.h"
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

void SelectCanvasAction::collectResults(Shape **selShape,
                                        ShapePart **selShapePart) {
  if(selectedShapes.size() > 0)
    *selShape = *selectedShapes.begin();
  if(selectedShapesParts.size() > 0)
    *selShapePart = *selectedShapesParts.begin();
}

void SelectCanvasAction::collectMultiResults(set<Shape *> *selShapes,
                                             set<ShapePart *> *selShapeParts) {
  *selShapes = selectedShapes;
  *selShapeParts = selectedShapesParts;
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

}

void SelectCanvasAction::colorSelected(ShapePart *shapePart, Color c) {
  shapePart->setColor(c);
}

bool SelectCanvasAction::handleSelected(ShapePart *shapePart) {
  if(shapePart == nullptr)
    return false;

  if(wholeShapeMode) {
    Shape *shape = shapePart->getParent();
    if(selectedShapes.find(shape) == selectedShapes.end()) {
      colorSelected(shape, selectedColor);
      selectedShapes.insert(shape);
      return true;
    }
    else {
      return false;
    }
  }
  else {
    if (selectedShapesParts.find(shapePart) == selectedShapesParts.end()) {
      colorSelected(shapePart, selectedColor);
      selectedShapesParts.insert(shapePart);
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
