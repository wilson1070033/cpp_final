#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>
#include "Map.h"
#include "LevelManager.h"
#include "../entities/GameObject.h"

using namespace std;

class Controller
{
private:
    Map* gameMap;
    LevelManager* levelManager;
    vector<GameObject*> gameObjects;
    int frogCrossings;  // 青蛙成功過河次數
    bool showLevelInfo; // 是否顯示關卡資訊

    // 清除螢幕的私有方法
    void clearScreen();

    // 關卡相關方法
    void generateVehicles();
    void generateObstacles();
    void checkLevelProgress();
    void displayGameInfo();
    bool checkFrogReachedGoal();
    void resetFrogPosition();

public:
    Controller();
    ~Controller();
    void initializeGame();
    void gameLoop();
    void cleanup();

    // 新增公開方法
    void showLevelInformation() { showLevelInfo = true; }
    LevelManager* getLevelManager() { return levelManager; }
};

#endif