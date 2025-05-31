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

Controller::Controller() : gameMap(nullptr), levelManager(nullptr), frogCrossings(0), showLevelInfo(true) {}

Controller::~Controller() {
    cleanup();
}

// 清除螢幕函式
void Controller::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Controller::initializeGame() {
    srand(static_cast<unsigned int>(time(0)));

    const int H = GAME_HEIGHT;
    const int W = GAME_WIDTH;
    int R[H] = {1, 1, 0, 0, 1, 0, 0, 0, 1, 1};

    gameMap = new Map(W, H, R);
    levelManager = new LevelManager();
    GameObject::setMap(gameMap);
    Map::setLevelManager(levelManager);  // 設置Map的LevelManager指標

    // 顯示歡迎資訊
    clearScreen();
    cout << "Welcome to Frogger Game!" << endl;
    cout << "Goal: Help the frog safely reach the other side!" << endl;
    cout << "Controls: Use arrow keys to move the frog" << endl;
    cout << "Warning: Avoid vehicles (C/M) and obstacles (O)" << endl;
    levelManager->displayLevelInfo();
    cout << "\nGame starting..." << endl;
    // 移除了等待輸入，直接開始遊戲
    usleep(1000000); // 僅顯示1秒介紹

    // 青蛙放在最前面，確保優先處理
    resetFrogPosition();

    // 根據關卡難度生成車輛和障礙物
    generateVehicles();
    generateObstacles();
}

void Controller::resetFrogPosition() {
    // 清理舊的青蛙
    for(auto it = gameObjects.begin(); it != gameObjects.end();) {
        if(dynamic_cast<Frog*>(*it)) {
            delete *it;
            it = gameObjects.erase(it);
        } else {
            ++it;
        }
    }

    // 在底部安全區域重新放置青蛙
    gameObjects.insert(gameObjects.begin(), new Frog(randBtw(15, 25), 9, 'F'));
}

void Controller::generateVehicles() {
    const int H = GAME_HEIGHT;
    const int W = GAME_WIDTH;
    int R[H] = {1, 1, 0, 0, 1, 0, 0, 0, 1, 1};

    // 清理舊的車輛
    for(auto it = gameObjects.begin(); it != gameObjects.end();) {
        if(dynamic_cast<Car*>(*it) || dynamic_cast<Moto*>(*it)) {
            delete *it;
            it = gameObjects.erase(it);
        } else {
            ++it;
        }
    }

    // 根據關卡難度生成車輛
    for(int i = 0; i < H; i++) {
        if(R[i] == 0) { // 只在道路上生成車輛
            int vehiclesInThisLane = levelManager->getVehiclesPerLane();

            for(int v = 0; v < vehiclesInThisLane; v++) {
                int x, d;

                if(i % 2 == 1) {
                    // 奇數行：從左到右
                    x = (W / vehiclesInThisLane) * v;
                    d = levelManager->calculateVehicleSpeed(2);
                } else {
                    // 偶數行：從右到左
                    x = W - 1 - (W / vehiclesInThisLane) * v;
                    d = -levelManager->calculateVehicleSpeed(2);
                }

                // 根據行數決定車輛類型
                if(i % 2 == 0) {
                    gameObjects.push_back(new Car(x, i, 'C', d));
                } else {
                    gameObjects.push_back(new Moto(x, i, 'M', d));
                }
            }
        }
    }
}

void Controller::generateObstacles() {
    const int H = GAME_HEIGHT;
    const int W = GAME_WIDTH;

    // 清理舊的障礙物
    for(auto it = gameObjects.begin(); it != gameObjects.end();) {
        if(dynamic_cast<Obstacle*>(*it)) {
            delete *it;
            it = gameObjects.erase(it);
        } else {
            ++it;
        }
    }

    // 根據關卡難度生成障礙物
    int obstacleCount = levelManager->getObstacleCount();
    for(int i = 0; i < obstacleCount; i++) {
        int ox = randBtw(0, W - 1);
        int oy = randBtw(1, H - 2); // 避免在起始和目標位置放置障礙物
        gameObjects.push_back(new Obstacle(ox, oy));
    }
}

bool Controller::checkFrogReachedGoal() {
    // 檢查青蛙是否到達目標區域（第一行，y=0）
    for(auto obj : gameObjects) {
        Frog* frog = dynamic_cast<Frog*>(obj);
        if(frog && frog->getY() == 0) {
            return true;
        }
    }
    return false;
}

void Controller::checkLevelProgress() {
    if(checkFrogReachedGoal()) {
        frogCrossings++;

        // 給予過河獎勵分數
        int crossingBonus = 50 * levelManager->getCurrentLevel();
        levelManager->addScore(crossingBonus);

        clearScreen();
        cout << "Frog crossed successfully! Earned " << crossingBonus << " points!" << endl;
        cout << "Currently crossed " << frogCrossings << " times" << endl;

        // 重置青蛙位置
        resetFrogPosition();

        // 檢查是否完成關卡
        if(levelManager->checkLevelComplete()) {
            clearScreen();
            cout << "Level Complete!" << endl;

            if(!levelManager->isMaxLevel()) {
                levelManager->nextLevel();
                frogCrossings = 0;

                // 重新生成車輛和障礙物以適應新關卡
                generateVehicles();
                generateObstacles();

                showLevelInfo = true;
                usleep(1000000); // 顯示1秒關卡資訊
            } else {
                // 遊戲完全通關
                cout << "Congratulations! You have completed all levels!" << endl;
                cout << "You are the true Frogger Master!" << endl;
                usleep(2000000);
                return;
            }
        }

        usleep(500000); // 0.5秒慶祝時間
    }
}

void Controller::displayGameInfo() {
    cout << "Level: " << levelManager->getCurrentLevel()
         << " | Score: " << levelManager->getCurrentLevelScore()
         << "/" << levelManager->getScoreRequiredForNextLevel()
         << " | Crossings: " << frogCrossings << endl;
}

void Controller::gameLoop() {
    while(true) {
        clearScreen();

        // 顯示關卡資訊（僅在特定時機）
        if(showLevelInfo) {
            levelManager->displayLevelInfo();
            showLevelInfo = false;
            usleep(500000); // 顯示0.5秒
            continue;
        }

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
            cout << "\nGAME OVER!" << endl;
            cout << "Final Level: " << levelManager->getCurrentLevel() << endl;
            cout << "Final Score: " << levelManager->getCurrentLevelScore() << endl;
            cout << "Total Crossings: " << frogCrossings << endl;
            cout << "\nThanks for playing!" << endl;
            usleep(2000000);
            return;
        }

        // 檢查關卡進度
        checkLevelProgress();

        // 顯示遊戲資訊
        displayGameInfo();

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

    if(levelManager) {
        delete levelManager;
        levelManager = nullptr;
    }
}