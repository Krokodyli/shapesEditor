#pragma once

#include "color.h"
#include "point.h"

#include <vector>
#include <string>

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

  static const double equalEdgesConstraintTolerance;

  static const int constraintIconSize;

  static std::string resourcesPath;

  static void addPathFromArg(char *pathFromArg);

  static const std::string getResourcePath(std::string resource);

  static Color getRandomColorForConstraint();

  static const std::vector<std::string> imagesPaths;

  static const std::string fontPath;

  static const int defaultModeButtonImage;
  static const int polygonModeButtonImage;
  static const int circleModeButtonImage;
  static const int constraintModeButtonImage;

  static const int deleteButtonImage;
  static const int insertVertexButtonImage;

  static const int lockedIconImage;

  static const int fixedCenterConstraintButtonImage;
  static const int fixedRadiusConstraintButtonImage;

  static const int fixedLengthConstraintButtonImage;
  static const int equalEdgesConstraintButtonImage;
  static const int parallelEdgesConstraintButtonImage;
  static const int tangentConstraintButtonImage;
  static const int antialiasingButtonImage;
};
