#ifndef UNTITLED_DRAGGABLE_H
#define UNTITLED_DRAGGABLE_H

#include "../ecs/Component.h"

struct Draggable: public Component {
    Draggable(double targetSize) : targetSize(targetSize) {}

    double targetSize;
};

#endif //UNTITLED_DRAGGABLE_H
