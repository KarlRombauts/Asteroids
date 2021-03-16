#ifndef UNTITLED_DEATH_H
#define UNTITLED_DEATH_H

#include "../ecs/Entity.h"

struct Death {
    Death(Entity *entity): entity(entity) {}

    Entity* entity;
};


#endif //UNTITLED_DEATH_H
