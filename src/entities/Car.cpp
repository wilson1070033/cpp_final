#include "../../include/entities/Car.h"

using namespace std;

Car::Car(int x, int y, char c, int d) : Vehicle(x, y, c, d) {}

bool Car::move() {
    x = x + d;
    if(x < 0) x = 39;
    if(x > 39) x = 0;
    return setXY(x, y, getIcon());
}