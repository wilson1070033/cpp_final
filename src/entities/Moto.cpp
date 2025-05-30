#include "../../include/entities/Moto.h"

using namespace std;

Moto::Moto(int x, int y, char c, int d) : Vehicle(x, y, c, d) {}

bool Moto::move() {
    x = x + d/2;
    if(x < 0) x = 39;
    if(x > 39) x = 0;
    return setXY(x, y, getIcon());
}