#ifndef UNTITLED_TRANSFORM_H
#define UNTITLED_TRANSFORM_H

#include "../ecs/Component.h"
#include "../Vec2.h"

enum class OutOfBoundsBehaviour {
    WRAP = 0,
    BOUNCE = 1,
    DESTROY = 2,
};

struct Transform : public Component {
    Transform(double x, double y, double rotation,
              OutOfBoundsBehaviour outOfBoundsBehaviour)
            : position(x, y), rotation(rotation), outOfBoundsBehaviour(outOfBoundsBehaviour) {}

    Vec2 position;
    double rotation;

    OutOfBoundsBehaviour outOfBoundsBehaviour;
};

#endif //UNTITLED_TRANSFORM_H
