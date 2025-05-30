#include "../../include/entities/Vehicle.h"

using namespace std;

Vehicle::Vehicle(int x, int y, char c, int d) : GameObject(x, y, c) {
    this->d = d;
}