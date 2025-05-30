#ifndef FROG_H
#define FROG_H

#include "GameObject.h"

class Frog : public GameObject
{
public:
    Frog(int x, int y, char c);
    bool move() override;
};

#endif