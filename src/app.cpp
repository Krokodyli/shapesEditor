#include "app.h"

App::~App() {
  delete canvas;
  delete canvasManager;
  delete toolbar;
  delete inputInfo;
  delete drawManager;
}

void App::execute() {
  setup();
  isRunning = true;
  while(isRunning) {
    handleEvents();
    update();
    draw();
  }
}

void App::setup() {
  canvas = new Canvas();
  canvasManager = new CanvasManager();
  toolbar = new Toolbar();
}

void App::draw() {
  canvas->draw(drawManager);
  toolbar->draw(drawManager);
}

void App::update() {
  inputInfo->update();
  canvas->update(canvasManager, inputInfo);
}

void App::handleEvents() { }
