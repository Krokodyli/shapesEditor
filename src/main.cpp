#include "sfmlApp.h"

int main() {
  App *app = new SFMLApp(Point(1200, 600));
  app->execute();
  return 0;
}
