#pragma once

#include <set>

#include "canvasAction.h"
#include "selectAction.h"
#include "color.h"

using std::vector;
using std::set;

class Shape;

class SelectCanvasAction : public CanvasAction {
 private:
  vector<Shape*> selectedShapes;
  vector<ShapePart*> selectedShapesParts;

  bool multiselectMode;
  bool deselectMode;
  bool coloringMode;

  Color unselectedColor;
  Color selectedColor;

  bool wholeShapeMode;
  bool isDeselecting;
  Point p;

  void colorSelected(Shape *shape, Color c);
  void colorSelected(ShapePart *shapePart, Color c);
  bool handleSelected(ShapePart *shapePart);
  bool doSelect(std::vector<Shape *> *shapes);
  void doDeselect();
  bool isAlreadySelected(ShapePart *shapePart);
  bool isAlreadySelected(Shape *shape);
public:
  SelectCanvasAction(bool _multiselectMode,
                     bool _deselectMode,
                     bool coloringMode = false,
                     Color _unselectedColor = Color(),
                     Color _selectedColor = Color());

  void select(Point _p, bool _wholeShapeMode = false);
  void deselect();

  vector<Shape*> getSelectedShapes();
  vector<ShapePart*> getSelectedShapeParts();
  bool isSomethingSelected();

  virtual void doAction(std::vector<Shape *> *shapes);
  virtual bool canDoAction(std::vector<Shape *> *shapes);
};
