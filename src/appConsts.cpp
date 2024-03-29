#include "appConsts.h"

#include <filesystem>
#include <vector>

const Point AppConsts::appSize = Point(1200, 900);
const std::string AppConsts::appTitle = "Shapes Editor";
const int AppConsts::framerateLimit = 60;

const Color AppConsts::canvasColor = Color(230, 255, 230);
const Color AppConsts::shapeColor = Color(0, 0, 0);
const Color AppConsts::selectedShapeColor = Color(255, 0, 0);

const int AppConsts::vertexSize = 3;

const Color AppConsts::toolbarColor = Color(76, 140, 74);
const Color AppConsts::activeButtonColor = Color(10, 60, 10);
const Color AppConsts::inactiveButtonColor = Color(20, 100, 20);
const int AppConsts::toolbarWidth = 200;
const Point AppConsts::buttonSize = Point(50, 50);
const int AppConsts::doubleClickThreshold = 300;

const int AppConsts::ringSelectionTolerance = 4;
const int AppConsts::vertexSelectionTolerance = 16;
const double AppConsts::edgeSelectionTolerance = 0.2;

const double AppConsts::equalEdgesConstraintTolerance = 4;

const int AppConsts::constraintIconSize = 25;

std::string AppConsts::resourcesPath = "resources/";

void AppConsts::addPathFromArg(char *pathFromArg) {
  std::filesystem::path rootPath = std::filesystem::current_path();
  std::filesystem::path p = pathFromArg;
  rootPath /= p.parent_path();
  rootPath = std::filesystem::weakly_canonical(rootPath);
  resourcesPath = rootPath.string() + "/resources/";
}


const std::string AppConsts::getResourcePath(std::string resource) {
  return resourcesPath + resource;
}

Color AppConsts::getRandomColorForConstraint() {
  return Color((rand() % 255 + 255) / 2, (rand() % 255 + 255) / 2,
               (rand() % 255 + 255) / 2);
}

const std::vector<std::string> AppConsts::imagesPaths = {
  "defaultIcon.png",
  "polygonIcon.png",
  "circleIcon.png",
  "constraintIcon.png",
  "deleteIcon.png",
  "newVertexIcon.png",
  "locked.png",
  "lockedCenterIcon.png",
  "lockedRingIcon.png",
  "fixedLengthIcon.png",
  "equalEdgesIcon.png",
  "parallelEdgesIcon.png",
  "tangentIcon.png",
  "antialiasingIcon.png"
};

const std::string AppConsts::fontPath = "font.ttf";

const int AppConsts::defaultModeButtonImage = 0;
const int AppConsts::polygonModeButtonImage = 1;
const int AppConsts::circleModeButtonImage = 2;
const int AppConsts::constraintModeButtonImage = 3;
const int AppConsts::deleteButtonImage = 4;
const int AppConsts::insertVertexButtonImage = 5;
const int AppConsts::lockedIconImage = 6;
const int AppConsts::fixedCenterConstraintButtonImage = 7;
const int AppConsts::fixedRadiusConstraintButtonImage = 8;

const int AppConsts::fixedLengthConstraintButtonImage = 9;
const int AppConsts::equalEdgesConstraintButtonImage = 10;
const int AppConsts::parallelEdgesConstraintButtonImage = 11;
const int AppConsts::tangentConstraintButtonImage = 12;
const int AppConsts::antialiasingButtonImage = 13;
