#include "sfmlApp.h"
#include "sfmlDrawManager.h"
#include "sfmlInputInfo.h"
#include "sfmlCanvasDrawManager.h"
#include <string>

SFMLApp::SFMLApp(Point _size) : App(_size) { }

SFMLApp::~SFMLApp() {
  App::~App();
  delete window;
}

void SFMLApp::setup() {
  App::initialSetup();
  window = new sf::RenderWindow(sf::VideoMode(size.x, size.y, 32),
                                AppConsts::appTitle, sf::Style::Titlebar |
                                sf::Style::Close);
  window->setFramerateLimit(AppConsts::framerateLimit);
  drawManager = new SFMLDrawManager(window);
  inputInfo = new SFMLInputInfo(window);
  canvasDrawManager = new SFMLCanvasDrawManager(canvasSize);
  App::setup();

  clock.restart();
}

void SFMLApp::draw() {
  App::draw();

  fps = 1000 / clock.restart().asMilliseconds();
  if(showFPS)
    drawManager->drawText("fps: " + std::to_string(fps),
                          AppConsts::appSize.x - 100, 0, 20, Color(0, 0, 0));

  window->display();
}

void SFMLApp::handleEvents() {
  sf::Event e;
  while (window->pollEvent(e)) {
    if (e.type == sf::Event::Closed)
      isRunning = false;
  }
}
