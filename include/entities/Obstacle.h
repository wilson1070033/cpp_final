#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"

class Obstacle : public GameObject
{
public:
    Obstacle(int x, int y);
    bool move() override;
};

#endif