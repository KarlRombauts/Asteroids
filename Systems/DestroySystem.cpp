//
// Created by Karl Rombauts on 18/4/21.
//

#include <iostream>
#include "DestroySystem.h"
#include "../Components/BoundingCircle.h"

void DestroySystem::update(EntityManager &entities) {
    for(Entity *entity: entities.getEntitiesWith<Destroy>()) {

        if(entity->has<BoundingCircle>()) {
            std::cout << "BIG WHOOPS" << std::endl;
        }

        entities.destroy(entity);
    }
}
