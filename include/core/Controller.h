#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "Map.h"
#include "../entities/GameObject.h"

using namespace std;

class Controller
{
private:
    Map* gameMap;
    vector<GameObject*> gameObjects;

    // 清除螢幕的私有方法
    void clearScreen();

public:
    Controller();
    ~Controller();
    void initializeGame();
    void gameLoop();
    void cleanup();
};

#endif