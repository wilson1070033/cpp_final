#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle
{
public:
    Car(int x, int y, char c, int d);
    bool move() override;
};

#endif