#ifndef UNTITLED_TRANSFORM_H
#define UNTITLED_TRANSFORM_H

#include "../ecs/Component.h"
#include "../Vec2.h"

struct Transform : public Component {
    Transform() : position(Vec2(0,0)), rotation(0), scale(Vec2(1,1)) {}
    Transform(Vec2 position, double rotation, Vec2 scale)
            : position(position), rotation(rotation), scale(scale) {}

    Vec2 position;
    Vec2 scale;
    double rotation;
};

#endif //UNTITLED_TRANSFORM_H
