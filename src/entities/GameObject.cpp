#include "../../include/entities/GameObject.h"

using namespace std;

Map* GameObject::map = nullptr;

GameObject::GameObject(int x, int y, char c) : x(x), y(y), c(c) {
    setXY(x, y, c);
}

bool GameObject::setXY(int x, int y, char c)
{
    if(map) {
        return map->setXY(x, y, c);
    }
    return false;
}