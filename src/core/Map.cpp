#include "../../include/core/Map.h"
#include <iostream>

using namespace std;

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
    cout << "Score: " << score << endl;
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
            cout << grid[i][j];
        cout << endl;
    }
    grid = g0;
    return 0;
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