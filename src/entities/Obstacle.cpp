#include "../../include/entities/Obstacle.h"

using namespace std;

Obstacle::Obstacle(int x, int y) : GameObject(x, y, 'O') {}

bool Obstacle::move() {
    return true;
}