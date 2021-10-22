#pragma once

#include "color.h"
#include "point.h"

#include <vector>
#include <iostream>

class AppConsts {
 public:
  static const Point appSize;
  static const std::string appTitle;
  static const int framerateLimit;

  static const Color canvasColor;
  static const Color shapeColor;
  static const Color selectedShapeColor;

  static const int vertexSize;

  static const Color toolbarColor;
  static const Color activeButtonColor;
  static const Color inactiveButtonColor;
  static const Color disabledButtonColor;
  static const int toolbarWidth;
  static const Point buttonSize;
  static const int doubleClickThreshold;

  static const int ringSelectionTolerance;
  static const int vertexSelectionTolerance;
  static const double edgeSelectionTolerance;

  static std::string resourcesPath;
  static void addPathFromArg(char *pathFromArg);
  static const std::string getResourcePath(std::string resource);

  static const std::vector<std::string> imagesPaths;

  static const int defaultModeButtonImage;
};
