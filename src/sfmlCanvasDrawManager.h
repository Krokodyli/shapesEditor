#include "canvasDrawManager.h"

#include <SFML/Graphics.hpp>

class SFMLCanvasDrawManager : public CanvasDrawManager {
protected:
  Point size;

  sf::Image image;
  sf::Texture texture;
  sf::Sprite sprite;

  sf::Color color;

  virtual void putPixel(int x, int y);
  virtual void prepareColor(Color c);

  sf::Color colorToSFMLColor(Color c);
public:
  SFMLCanvasDrawManager(Point _size);
  virtual ~SFMLCanvasDrawManager();

  virtual void display(DrawManager *drawManager);
};
