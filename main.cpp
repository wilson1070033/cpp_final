#include "include//core/Controller.h"

using namespace std;

int main()
{
    Controller controller;
    controller.initializeGame();
    controller.gameLoop();
    controller.cleanup();
    return 0;
}