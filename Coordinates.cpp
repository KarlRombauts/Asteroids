//
// Created by Karl Rombauts on 14/3/21.
//


#include "Coordinates.h"
#include "Vec2.h"

bool CoordinateSpace::isOutOfBounds(Vec2 vector) {
    return vector.x < minX || vector.x > maxX ||
           vector.y < minY || vector.y > maxY;
}

