//
// Created by Karl Rombauts on 15/3/21.
//

#include "OutOfBoundsSystem.h"
#include "../Components/Transform.h"
#include "../GameState.h"

void OutOfBoundsSystem::update(EntityManager &entities) {
    for (Entity *entity: entities.getEntitiesWith<Transform>()) {
        Vec2 position = entity->get<Transform>()->position;
        if (position.magnitude() > gameState.worldCoordinates.distanceToCorner() + 30) {
            entities.destroy(entity);
        }
    }
}
