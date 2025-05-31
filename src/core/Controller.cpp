#include "../../include/core/Controller.h"
#include "../../include/entities/Frog.h"
#include "../../include/entities/Obstacle.h"
#include "../../include/entities/Car.h"
#include "../../include/entities/Moto.h"
#include "../../include/utils/Utils.h"
#include "../../include/common/GameConstants.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

Controller::Controller() : gameMap(nullptr) {}

Controller::~Controller() {
    cleanup();
}

// 清除螢幕函式
void Controller::clearScreen() {
    cout << "\033[2J\033[1;1H" << flush;
}

void Controller::initializeGame() {
    srand(static_cast<unsigned int>(time(0)));

    const int H = GAME_HEIGHT;
    const int W = GAME_WIDTH;
    int R[H] = {1, 1, 0, 0, 1, 0, 0, 0, 1, 1};

    gameMap = new Map(W, H, R);
    GameObject::setMap(gameMap);

    // 青蛙放在最前面，確保優先處理
    gameObjects.push_back(new Frog(randBtw(15, 25), 9, 'F'));

    int x, d;
    for(int i = 0; i < H; i++)
    {
        int ox = randBtw(0, W - 1);
        int oy = randBtw(0, H - 1);
        gameObjects.push_back(new Obstacle(ox, oy));

        if(R[i] == 0) {
            if(i % 2 == 1) {
                x = 0;
                d = 2;
            }
            else {
                x = W - 1;
                d = -2;
            }

            if(i % 2 == 0) gameObjects.push_back(new Car(x, i, 'C', d));
            else gameObjects.push_back(new Moto(x, i, 'M', d));
        }
    }
}

void Controller::gameLoop() {
    while(true) {
        clearScreen();

        // 在每個循環開始時重置地圖
        gameMap->resetGrid();

        bool gameOver = false;

        // 移動所有物體並檢查碰撞
        for(auto o : gameObjects) {
            if(!o->move()) {
                gameOver = true;
                break;
            }
        }

        if(gameOver) {
            clearScreen();
            cout << "\n\n\n===== GAME OVER =====" << endl;
            usleep(GAME_UPDATE_DELAY);
            return;
        }

        // 顯示遊戲畫面
        GameObject::draw();

        usleep(GAME_UPDATE_DELAY);
    }
}

void Controller::cleanup() {
    for(auto obj : gameObjects) {
        delete obj;
    }
    gameObjects.clear();

    if(gameMap) {
        delete gameMap;
        gameMap = nullptr;
    }
}