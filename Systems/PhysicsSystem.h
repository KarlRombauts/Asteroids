//
// Created by Karl Rombauts on 14/3/21.
//

#ifndef UNTITLED_PHYSICSSYSTEM_H
#define UNTITLED_PHYSICSSYSTEM_H


#include "System.h"
#include "../Events/CollisionEvent.h"
#include "../ecs/EventManager.h"

class PhysicsSystem: public System, public EventListener<CollisionEvent> {

public:
    void update(EntityManager &entities, double dt) override;

    void notify(CollisionEvent event) override;
};


#endif //UNTITLED_PHYSICSSYSTEM_H
