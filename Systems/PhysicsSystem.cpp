#include <iostream>
#include "PhysicsSystem.h"
#include "../Components/Moveable.h"
#include "../Components/Transform.h"
#include "../GameState.h"
#include "../Components/GravityForce.h"


void PhysicsSystem::update(EntityManager &entities, double dt) {
    for (Entity *entity: entities.getEntitiesWith<Moveable, Transform>()) {
        for (Entity *gravityEntity: entities.getEntitiesWith<GravityForce, Transform>()) {
            Vec2 diff = entity->get<Transform>()->position -
                        gravityEntity->get<Transform>()->position;
            double distance = diff.getMagnitude();

            double forceMagnitude =
                    gravityEntity->get<GravityForce>()->mass / pow(distance, 2);

            Vec2 force = (diff / diff.getMagnitude()) * forceMagnitude;
            entity->get<Moveable>()->acceleration += force;
        }

        Moveable *moveable = entity->get<Moveable>();
        Transform *transform = entity->get<Transform>();

        moveable->velocity =
                moveable->velocity + moveable->acceleration * dt / 1000;
        transform->position =
                transform->position + moveable->velocity * dt / 1000;


        if (gameState.isOutOfBounds(transform->position)) {
            if (transform->outOfBoundsBehaviour ==
                OutOfBoundsBehaviour::DESTROY) {
                entities.destroy(entity);
            }

            CoordinateSpace world = gameState.getWorldCoordinates();
            if (transform->position.x < world.minX) {
                if (transform->outOfBoundsBehaviour ==
                    OutOfBoundsBehaviour::WRAP) {
                    transform->position.x = world.maxX;
                } else if (transform->outOfBoundsBehaviour ==
                           OutOfBoundsBehaviour::BOUNCE) {
                    transform->position.x = world.minX;
                    moveable->velocity.x *= -1;
                }
            }

            if (transform->position.x > world.maxX) {
                if (transform->outOfBoundsBehaviour ==
                    OutOfBoundsBehaviour::WRAP) {
                    transform->position.x = world.minX;
                } else if (transform->outOfBoundsBehaviour ==
                           OutOfBoundsBehaviour::BOUNCE) {
                    transform->position.x = world.maxX;
                    moveable->velocity.x *= -1;
                }
            }

            if (transform->position.y < world.minY) {
                if (transform->outOfBoundsBehaviour ==
                    OutOfBoundsBehaviour::WRAP) {
                    transform->position.y = world.maxY;
                } else if (transform->outOfBoundsBehaviour ==
                           OutOfBoundsBehaviour::BOUNCE) {
                    transform->position.y = world.minY;
                    moveable->velocity.y *= -1;
                }
            }

            if (transform->position.y > world.maxY) {
                if (transform->outOfBoundsBehaviour ==
                    OutOfBoundsBehaviour::WRAP) {
                    transform->position.y = world.minY;
                } else if (transform->outOfBoundsBehaviour ==
                           OutOfBoundsBehaviour::BOUNCE) {
                    transform->position.y = world.maxY;
                    moveable->velocity.y *= -1;
                }
            }
        }

        moveable->acceleration = Vec2(0, 0);
    }
}

void PhysicsSystem::notify(CollisionEvent event) {
    std::cout << "Collision!" << std::endl;
}

