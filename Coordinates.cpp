#include "Coordinates.h"
#include "Vec2.h"

double CoordinateSpace::distanceToCorner() {
    return Vec2(maxX, maxY).magnitude();
}

