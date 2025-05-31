#include "../../include/core/LevelManager.h"
#include <iostream>
#include <string>

using namespace std;

LevelManager::LevelManager() {
    currentLevel = 1;
    maxLevel = 10;  // 最多10關
    currentLevelScore = 0;
    levelCompleted = false;

    // 初始化第一關的參數
    resetLevel();
}

void LevelManager::nextLevel() {
    if (currentLevel < maxLevel) {
        currentLevel++;
        resetLevel();
        cout << "\nCongratulations! Entering Level " << currentLevel << "!" << endl;
        displayLevelInfo();
    }
}

void LevelManager::resetLevel() {
    currentLevelScore = 0;
    levelCompleted = false;

    // 根據關卡調整難度參數
    vehiclesPerLane = 1 + (currentLevel - 1) / 2;  // 每兩關增加一輛車
    vehicleSpeedMultiplier = 1.0f + (currentLevel - 1) * 0.2f;  // 每關增加20%速度
    obstacleCount = 3 + (currentLevel - 1);  // 每關增加一個障礙物
    scoreRequiredForNextLevel = 50 + (currentLevel - 1) * 30;  // 每關需要更多分數

    // 限制最大值避免遊戲過於困難
    if (vehiclesPerLane > 4) vehiclesPerLane = 4;
    if (vehicleSpeedMultiplier > 3.0f) vehicleSpeedMultiplier = 3.0f;
    if (obstacleCount > 8) obstacleCount = 8;
}

bool LevelManager::checkLevelComplete() {
    if (currentLevelScore >= scoreRequiredForNextLevel && !levelCompleted) {
        levelCompleted = true;
        return true;
    }
    return false;
}

void LevelManager::addScore(int points) {
    currentLevelScore += points;

    // 根據關卡給予額外獎勵
    if (currentLevel > 1) {
        int bonus = (currentLevel - 1) * 2;  // 高關卡額外獎勵
        currentLevelScore += bonus;
    }
}

void LevelManager::resetScore() {
    currentLevelScore = 0;
}

int LevelManager::calculateVehicleSpeed(int baseSpeed) const {
    // 確保速度至少為1，並且根據難度調整
    int adjustedSpeed = static_cast<int>(baseSpeed * vehicleSpeedMultiplier);
    if (adjustedSpeed == 0) adjustedSpeed = 1;
    return adjustedSpeed;
}

int LevelManager::getRequiredCrossings() const {
    // 根據關卡決定需要成功過河的次數
    return 2 + (currentLevel - 1);
}

void LevelManager::displayLevelInfo() const {
    cout << "\n╔═══════════════════════════════════╗" << endl;
    cout << "║            LEVEL INFO             ║" << endl;
    cout << "╠═══════════════════════════════════╣" << endl;
    cout << "║ Current Level: " << currentLevel << " / " << maxLevel << "                ║" << endl;
    cout << "║ Required Score: " << scoreRequiredForNextLevel << " points              ║" << endl;
    cout << "║ Current Score: " << currentLevelScore << " points               ║" << endl;
    cout << "║ Vehicles/Lane: " << vehiclesPerLane << "                     ║" << endl;
    cout << "║ Speed Multiplier: " << vehicleSpeedMultiplier << "x                ║" << endl;
    cout << "║ Obstacles: " << obstacleCount << "                        ║" << endl;
    cout << "╚═══════════════════════════════════╝" << endl;
    cout << getLevelDescription() << endl;
}

string LevelManager::getLevelDescription() const {
    switch(currentLevel) {
        case 1:
            return "Level 1: Welcome! Take it slow and steady!";
        case 2:
            return "Level 2: More traffic ahead, stay alert!";
        case 3:
            return "Level 3: Motorcycles appear, speed increases!";
        case 4:
            return "Level 4: Obstacles everywhere, proceed carefully!";
        case 5:
            return "Level 5: High-speed challenge, quick reflexes needed!";
        case 6:
            return "Level 6: Heavy vehicles, nowhere to hide!";
        case 7:
            return "Level 7: Chaotic traffic, mind-bending patterns!";
        case 8:
            return "Level 8: Hell mode, life and death situation!";
        case 9:
            return "Level 9: Extreme speed, supernatural challenge!";
        case 10:
            return "Level 10: Ultimate test, become the Frog King!";
        default:
            return "Congratulations! You've completed all levels! You are the true Frog Master!";
    }
}