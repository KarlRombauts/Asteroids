//
// Created by Karl Rombauts on 14/3/21.
//

#ifndef UNTITLED_PHYSICSSYSTEM_H
#define UNTITLED_PHYSICSSYSTEM_H


#include "System.h"

class PhysicsSystem: public System {

public:
    void update(EntityManager &entities, double dt) override;
};


#endif //UNTITLED_PHYSICSSYSTEM_H
