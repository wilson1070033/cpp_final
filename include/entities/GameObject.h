#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../core/Map.h"

class GameObject
{
protected:
    int x, y;
    const char c;
    static Map* map;

public:
    GameObject(int x, int y, char c);
    char getIcon() {return c;}
    int getX() {return x;}
    int getY() {return y;}
    virtual bool move() = 0;
    bool setXY(int x, int y, char c);
    static void setMap(Map* m) {map = m;}
    static void draw() {map->draw();}
};

#endif