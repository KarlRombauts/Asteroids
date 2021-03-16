//
// Created by Karl Rombauts on 14/3/21.
//

#include "CollisionSystem.h"
#include "../Components/Transform.h"
#include "../Globals.h"
#include "../Events/CollisionEvent.h"
#include "../Components/Identity.h"
#include "../Events/AsteroidHitEvent.h"
#include "../Events/Death.h"
#include "../Events/SpaceShipHitEvent.h"
#include "../Components/Collision.h"
#include "../Components/Asteroid.h"
#include "../Components/SpaceShip.h"
#include "../Components/Bullet.h"
#include "../Components/Moveable.h"
#include "../Components/BlackHole.h"

void CollisionSystem::update(EntityManager &entities, double dt) {
    std::vector<Entity *> rigidBodyEntitites = entities.getEntitiesWith<Transform, Collision>();

    for (Entity *entity1: rigidBodyEntitites) {
        Transform *entity1Transform = entity1->get<Transform>();
        for (Entity *entity2: rigidBodyEntitites) {
            if (entity1 == entity2) { continue; }

            Transform *entity2Transform = entity2->get<Transform>();

            Vec2 diff = (entity1Transform->position - entity2Transform->position);


            if (diff.getMagnitude() < entity1->get<Collision>()->radius + entity2->get<Collision>()->radius) {
                handleCollision(entities, entity1, entity2);
            }
        }
    }
}

void CollisionSystem::handleCollision(
        EntityManager &entities, Entity *entity1, Entity *entity2) {

    if (entity1->has<Asteroid>() && entity2->has<Bullet>()) {
        eventManager.emit<AsteroidHitEvent>(entity1, entity2);
        Asteroid* asteroidComponent = entity1->get<Asteroid>();
        Transform* transform = entity1->get<Transform>();

        if (asteroidComponent->size >= 2) {
            Entity* asteroid1 = entities.createAsteroid(asteroidComponent->size / (float) 2);
            Entity* asteroid2 = entities.createAsteroid(asteroidComponent->size / (float) 2);

            asteroid1->get<Transform>()->position = transform->position;
            asteroid2->get<Transform>()->position = transform->position;
        }

        entities.destroy(entity1);
        entities.destroy(entity2);
    }

    if (entity1->has<Asteroid>() && entity2->has<SpaceShip>()) {
        entities.destroy(entity2);
    }

    if (entity1->has<BlackHole>()) {
        entities.destroy(entity2);
    }
}
