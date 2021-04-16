#include <iostream>
#include "PhysicsSystem.h"
#include "../Components/Moveable.h"
#include "../Components/Transform.h"
#include "../GameState.h"
#include "../Components/GravityForce.h"
#include "../Components/Child.h"


void PhysicsSystem::update(EntityManager &entities, double dt) {
    for (Entity *entity: entities.getEntitiesWith<Moveable, Transform>()) {
        for (Entity *gravityEntity: entities.getEntitiesWith<GravityForce, Transform>()) {
            Vec2 diff = entity->get<Transform>()->position -
                        gravityEntity->get<Transform>()->position;
            double distance = diff.magnitude();

            double forceMagnitude =
                    gravityEntity->get<GravityForce>()->mass / pow(distance, 2);

            Vec2 force = (diff / diff.magnitude()) * forceMagnitude;
            entity->get<Moveable>()->acceleration += force;
        }

        Moveable *moveable = entity->get<Moveable>();
        Transform *transform = entity->get<Transform>();

        moveable->acceleration -= moveable->velocity * moveable->drag;

        moveable->velocity =
                moveable->velocity + moveable->acceleration * dt / 1000;
        transform->position =
                transform->position + moveable->velocity * dt / 1000;

        moveable->acceleration = Vec2(0, 0);

        if(entity->has<Child>()) {
            Entity *child = entity->get<Child>()->child;
            if (child->has<Transform>()) {
                child->get<Transform>()->position = transform->position;
            }
        }

    }
}

void PhysicsSystem::notify(CollisionEvent event) {
    std::cout << "Collision!" << std::endl;
}

