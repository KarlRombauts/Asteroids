//
// Created by Karl Rombauts on 14/3/21.
//

#ifndef UNTITLED_COLLISIONEVENT_H
#define UNTITLED_COLLISIONEVENT_H

#include "../ecs/Entity.h"

struct CollisionEvent {
    CollisionEvent(Entity *entity1, Entity *entity2)
            : entity1(entity1), entity2(entity2) {}

    Entity *entity1;
    Entity *entity2;
};

#endif //UNTITLED_COLLISIONEVENT_H
