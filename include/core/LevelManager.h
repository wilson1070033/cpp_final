#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include <string>

using namespace std;

class LevelManager {
private:
    int currentLevel;
    int maxLevel;
    int vehiclesPerLane;
    float vehicleSpeedMultiplier;
    int obstacleCount;
    int scoreRequiredForNextLevel;
    int currentLevelScore;
    bool levelCompleted;

public:
    LevelManager();

    // 關卡管理
    void nextLevel();
    void resetLevel();
    bool checkLevelComplete();

    // Getter方法
    int getCurrentLevel() const { return currentLevel; }
    int getVehiclesPerLane() const { return vehiclesPerLane; }
    float getVehicleSpeedMultiplier() const { return vehicleSpeedMultiplier; }
    int getObstacleCount() const { return obstacleCount; }
    int getScoreRequiredForNextLevel() const { return scoreRequiredForNextLevel; }
    int getCurrentLevelScore() const { return currentLevelScore; }
    bool isLevelCompleted() const { return levelCompleted; }
    bool isMaxLevel() const { return currentLevel >= maxLevel; }

    // 分數管理
    void addScore(int points);
    void resetScore();

    // 難度計算
    int calculateVehicleSpeed(int baseSpeed) const;
    int getRequiredCrossings() const; // 需要過河的次數

    // 關卡資訊顯示
    void displayLevelInfo() const;
    string getLevelDescription() const;
};

#endif