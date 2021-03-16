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
    Transform(Vec2 position, double rotation, Vec2 scale,
              OutOfBoundsBehaviour outOfBoundsBehaviour)
            : position(position), rotation(rotation), scale(scale), outOfBoundsBehaviour(outOfBoundsBehaviour) {}

    Vec2 position;
    Vec2 scale;
    double rotation;

    OutOfBoundsBehaviour outOfBoundsBehaviour;
};

#endif //UNTITLED_TRANSFORM_H
