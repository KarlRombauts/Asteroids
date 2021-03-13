//
// Created by Karl Rombauts on 12/3/21.
//

#ifndef UNTITLED_SHIP_H
#define UNTITLED_SHIP_H


#include "Components/Transform.h"
#include "Vec2.h"

class Ship {
private:

    Vec2 position;
    Vec2 velocity;
    float rotation;
    float mass;
    double maxSpeed;

public:
    Ship(Vec2 position, float rotation, double maxSpeed, float mass);
    void update(double dt);
    void render();
};


#endif //UNTITLED_SHIP_H
