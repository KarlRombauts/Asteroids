#ifndef UNTITLED_COORDINATES_H
#define UNTITLED_COORDINATES_H


#include "Vec2.h"

struct CoordinateSpace {
    double minX;
    double maxX;
    double minY;
    double maxY;

    double distanceToCorner();
};


#endif //UNTITLED_COORDINATES_H
