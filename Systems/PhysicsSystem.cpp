#include <iostream>
#include "PhysicsSystem.h"
#include "../Components/Moveable.h"
#include "../Components/Transform.h"
#include "../Components/GravityForce.h"
#include "../Components/Child.h"


void PhysicsSystem::update(EntityManager &entities, double dt) {
    for (Entity *entity: entities.getEntitiesWith<Moveable, Transform>()) {
        for (Entity *gravityEntity: entities.getEntitiesWith<GravityForce, Transform>()) {
            Vec2 diff = gravityEntity->get<Transform>()->position - entity->get<Transform>()->position;
            double distance = diff.magnitude();

            double forceMagnitude =
                    gravityEntity->get<GravityForce>()->mass / pow(distance, 2);

            Vec2 force = diff.normalize().scale(forceMagnitude);
            entity->get<Moveable>()->acceleration += force;
        }

        Transform *transform = entity->get<Transform>();
        Moveable *moveable = entity->get<Moveable>();

        moveable->acceleration -= moveable->velocity * moveable->drag;

        moveable->velocity += moveable->acceleration * dt / 1000;
        transform->position += moveable->velocity * dt / 1000;
        transform->rotation += moveable->angularVelocity * dt / 1000;

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

