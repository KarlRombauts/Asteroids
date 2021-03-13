//
// Created by Karl Rombauts on 14/3/21.
//

#ifndef UNTITLED_MOVEABLE_H
#define UNTITLED_MOVEABLE_H


#include "../Vec2.h"

struct Moveable : public Component {
    Moveable(const Vec2 &velocity, const Vec2 &acceleration) : velocity(
            velocity), acceleration(acceleration) {}

    Vec2 velocity;
    Vec2 acceleration;
};


#endif //UNTITLED_MOVEABLE_H
