#include "sfmlApp.h"
#include "appConsts.h"

int main(int argc, char **argv) {
  AppConsts::addPathFromArg(argv[0]);
  App *app = new SFMLApp(AppConsts::appSize);
  app->execute();
  return 0;
}
