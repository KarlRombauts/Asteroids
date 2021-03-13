//
// Created by Karl Rombauts on 14/3/21.
//

#include "PhysicsSystem.h"
#include "../Components/Moveable.h"
#include "../Components/Transform.h"
#include "../GameState.h"


void PhysicsSystem::update(EntityManager &entities, double dt) {
    for (Entity* entity: entities.getEntitiesWith<Moveable, Transform>()) {
        Moveable* moveable = entity->get<Moveable>();
        Transform* transform = entity->get<Transform>();

        moveable->velocity = moveable->velocity + moveable->acceleration * dt;
        transform->position = transform->position + moveable->velocity * dt;



        if(gameState.isOutOfBounds(transform->position)) {
            CoordinateSpace world = gameState.getWorldCoordinates();
            if (transform->position.x < world.minX) {
                if (transform->outOfBoundsBehaviour == OutOfBoundsBehaviour::WRAP) {
                    transform->position.x = world.maxX;
                } else if (transform->outOfBoundsBehaviour == OutOfBoundsBehaviour::BOUNCE) {
                    transform->position.x = world.minX;
                    moveable->velocity.x *= -1;
                }
            }

            if (transform->position.x > world.maxX) {
                if (transform->outOfBoundsBehaviour == OutOfBoundsBehaviour::WRAP) {
                    transform->position.x = world.minX;
                } else if (transform->outOfBoundsBehaviour == OutOfBoundsBehaviour::BOUNCE) {
                    transform->position.x = world.maxX;
                    moveable->velocity.x *= -1;
                }
            }

            if (transform->position.y < world.minY) {
                if (transform->outOfBoundsBehaviour == OutOfBoundsBehaviour::WRAP) {
                    transform->position.y = world.maxY;
                } else if (transform->outOfBoundsBehaviour == OutOfBoundsBehaviour::BOUNCE) {
                    transform->position.y = world.minY;
                    moveable->velocity.y *= -1;
                }
            }

            if (transform->position.y > world.maxY) {
                if (transform->outOfBoundsBehaviour == OutOfBoundsBehaviour::WRAP) {
                    transform->position.y = world.minY;
                } else if (transform->outOfBoundsBehaviour == OutOfBoundsBehaviour::BOUNCE) {
                    transform->position.y = world.maxY;
                    moveable->velocity.y *= -1;
                }
            }
        }

    }
}

