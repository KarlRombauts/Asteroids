//
// Created by Karl Rombauts on 14/3/21.
//

#ifndef UNTITLED_COLLISIONSYSTEM_H
#define UNTITLED_COLLISIONSYSTEM_H


#include "System.h"

class CollisionSystem: public System {
public:
    void update(EntityManager &entities, double dt) override;

public:
    void handleCollision(EntityManager &entities, Entity *entity1,
                         Entity *entity2);
};


#endif //UNTITLED_COLLISIONSYSTEM_H
