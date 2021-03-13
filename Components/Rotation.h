#ifndef UNTITLED_ROTATION_H
#define UNTITLED_ROTATION_H

#include "../ecs/Component.h"

struct Rotation : public Component {
    explicit Rotation(double degrees) : degrees(degrees) {}
    double degrees;
};

#endif //UNTITLED_ROTATION_H


