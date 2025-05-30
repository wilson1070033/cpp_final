#ifndef VEHICLE_H
#define VEHICLE_H

#include "GameObject.h"

class Vehicle : public GameObject
{
protected:
    int d;

public:
    Vehicle(int x, int y, char c, int d);
    virtual bool move() = 0;
};

#endif