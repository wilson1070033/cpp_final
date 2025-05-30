#ifndef MOTO_H
#define MOTO_H

#include "Vehicle.h"

class Moto : public Vehicle
{
public:
    Moto(int x, int y, char c, int d);
    bool move() override;
};

#endif