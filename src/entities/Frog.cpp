#include "../../include/entities/Frog.h"
#include "../../include/common/GameConstants.h"
#include <conio.h>

using namespace std;

Frog::Frog(int x, int y, char c) : GameObject(x, y, c) {}

bool Frog::move() {
    if(kbhit()) {
        int oldX = x, oldY = y;
        char key = getch();

        if (key == -32) {
            key = getch();
            switch (key) {
                case UP:
                    if(y > 0) y--;
                    break;
                case DOWN:
                    if(y < 9) y++;
                    break;
                case LEFT:
                    if(x > 0) x--;
                    break;
                case RIGHT:
                    if(x < 39) x++;
                    break;
            }
        }

        if(map->getO(x, y)) {
            x = oldX;
            y = oldY;
        }

        if(x != oldX || y != oldY) map->addScore(1);
    }
    return setXY(x, y, getIcon());
}