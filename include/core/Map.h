#ifndef MAP_H
#define MAP_H

#include <vector>

using namespace std;

class Map
{
private:
    int W, H;
    int* R;
    const int P = 2;
    int score = 0;
    vector<vector<char>> grid, g0;

public:
    Map(int w, int h, int* r);
    int draw();
    void resetGrid();  // 新增重置地圖的方法
    bool setXY(int x, int y, char c);
    void addScore(int i) {score += 1;}
    bool getO(int x, int y);
};

#endif