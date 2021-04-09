//
// Created by Karl Rombauts on 10/4/21.
//

#include <iostream>
#include "ImpactCleanupSystem.h"
#include "../Components/Impact.h"

void ImpactCleanupSystem::update(EntityManager &entities, double dt) {
    for(Entity* entity: entities.getEntitiesWith<Impact>()) {
        entity->remove<Impact>();
    }
}
