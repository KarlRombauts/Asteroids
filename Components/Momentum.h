//
// Created by Karl Rombauts on 14/3/21.
//

#ifndef UNTITLED_MOMENTUM_H
#define UNTITLED_MOMENTUM_H


#include "../ecs/Component.h"

struct Momentum: public Component {
    Momentum(double x, double y) : x(x), y(y) {}

    double x;
    double y;
};


#endif //UNTITLED_MOMENTUM_H
