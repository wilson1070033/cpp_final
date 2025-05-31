#ifndef MAP_H
#define MAP_H

#include <vector>

using namespace std;

// 前向宣告
class LevelManager;

class Map
{
private:
    int W, H;
    int* R;
    int score = 0;
    vector<vector<char>> grid, g0;
    static LevelManager* levelManager; // 靜態指標指向關卡管理器

public:
    Map(int w, int h, int* r);
    int draw();
    void resetGrid();
    bool setXY(int x, int y, char c);
    void addScore(int i);
    bool getO(int x, int y);
    int getScore() const { return score; }

    // 關卡系統相關
    static void setLevelManager(LevelManager* lm) { levelManager = lm; }
    static LevelManager* getLevelManager() { return levelManager; }
};

#endif