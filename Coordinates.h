//
// Created by Karl Rombauts on 13/3/21.
//

#ifndef UNTITLED_COORDINATES_H
#define UNTITLED_COORDINATES_H


#include "Vec2.h"

struct CoordinateSpace {
    double minX;
    double maxX;
    double minY;
    double maxY;

    bool isOutOfBounds(Vec2 vector);

    double distanceToCorner();
};


#endif //UNTITLED_COORDINATES_H
