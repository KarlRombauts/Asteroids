#ifndef UNTITLED_IDENTITY_H
#define UNTITLED_IDENTITY_H

#include "../ecs/Component.h"

enum class EntityType {
   LASER = 0,
   ASTEROID = 1,
   SPACE_SHIP = 2,
};

struct Identity : public Component {
    Identity(EntityType identity) : type(identity) {}

    EntityType type;
};

#endif //UNTITLED_IDENTITY_H
