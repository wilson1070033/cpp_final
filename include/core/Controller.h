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

public:
    Controller();
    ~Controller();
    void initializeGame();
    void gameLoop();
    void cleanup();
};

#endif