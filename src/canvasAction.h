#pragma once

#include <vector>

using std::vector;

class Shape;

class CanvasAction {
public:
  virtual void doAction(std::vector<Shape*>* shapes) = 0;
  virtual bool canDoAction(std::vector<Shape*>* shapes) = 0;
};
