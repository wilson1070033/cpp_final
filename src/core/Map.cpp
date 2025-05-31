#include "../../include/core/Map.h"
#include "../../include/core/LevelManager.h"
#include <iostream>

using namespace std;

// 靜態成員初始化
LevelManager* Map::levelManager = nullptr;

bool Map::getO(int x, int y) {
    if(y >= 0 && y < H && x >= 0 && x < W) {
        if(g0[y][x] == 'O') return true;
    }
    return false;
}

Map::Map(int w, int h, int* r) : W(w), H(h), R(r) {
    grid = vector<vector<char>>(H, vector<char>(W, '.'));

    for(int i = 0; i < H; i++)
        if(R[i] == 1) grid[i] = vector<char>(W, '=');

    g0 = grid;

    for(int i = 0; i < H; i++)
    {
        if(R[i] == 0) {
            if(i % 2 == 1) grid[i][0] = 'C';
            else grid[i][W - 1] = 'C';
        }
    }
}

int Map::draw() {
    // 顯示總分數（如果有關卡管理器，顯示關卡分數）
    if(levelManager) {
        cout << "Total Score: " << score << " | Level Score: " << levelManager->getCurrentLevelScore() << endl;
    } else {
        cout << "Score: " << score << endl;
    }

    // 繪製地圖邊框
    cout << "┌";
    for(int j = 0; j < W; j++) cout << "─";
    cout << "┐" << endl;

    for(int i = 0; i < H; i++)
    {
        cout << "│";
        for(int j = 0; j < W; j++) {
            char cell = grid[i][j];

            // 顯示遊戲元素
            cout << cell;
        }
        cout << "│";

        // 在右側顯示額外資訊
        if(i == 0) {
            cout << "  TARGET ZONE";
        } else if(i == H-1) {
            cout << "  START ZONE";
        } else if(R[i] == 1) {
            cout << "  SAFE ZONE";
        } else {
            cout << "  DANGER ROAD";
        }

        cout << endl;
    }

    cout << "└";
    for(int j = 0; j < W; j++) cout << "─";
    cout << "┘" << endl;

    return 0;
}

void Map::resetGrid() {
    grid = g0;
}

void Map::addScore(int i) {
    score += i;

    // 如果有關卡管理器，也更新關卡分數
    if(levelManager) {
        levelManager->addScore(i);
    }
}

bool Map::setXY(int x, int y, char c) {
    if(y >= 0 && y < H && x >= 0 && x < W) {
        if(c == 'O') g0[y][x] = c;
        if(c == 'F' && grid[y][x] == 'C') return false;
        if(c == 'F' && grid[y][x] == 'M') return false;
        if(c == 'C' && grid[y][x] == 'F') return false;
        if(c == 'M' && grid[y][x] == 'F') return false;
        grid[y][x] = c;
    }
    return true;
}