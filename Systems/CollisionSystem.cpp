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

    if (entity1->has<Asteroid>() && entity2->has<Asteroid>()) {
        Collision* collision1 = entity1->get<Collision>();
        Collision* collision2 = entity2->get<Collision>();
        Transform *transform1 = entity1->get<Transform>();
        Transform *transform2 = entity2->get<Transform>();
        Moveable *moveable1 = entity1->get<Moveable>();
        Moveable *moveable2 = entity2->get<Moveable>();


        Vec2 diff = transform1->position - transform2->position;
        double overlap = diff.getMagnitude() - (collision1->radius + collision2->radius);

        Vec2 offset = (diff / diff.getMagnitude()) * overlap;

        double m1 = moveable1->mass;
        double m2 = moveable2->mass;

        transform1->position -= offset * (m2 / (m1 + m2));
        transform2->position += offset * (m1 / (m1 + m2));

        Vec2 p1 = transform1->position;
        Vec2 p2 = transform2->position;
        Vec2 v1 = moveable1->velocity;
        Vec2 v2 = moveable2->velocity;

        Vec2 newV1 = v1 - ((p1 - p2) * ((v1 - v2).dot(p1 - p2) / pow((p1- p2).getMagnitude(), 2))) * ((2 * m2) / (m1 + m2));
        Vec2 newV2 = v2 - ((p2 - p1) * ((v2 - v1).dot(p2 - p1) / pow((p2- p1).getMagnitude(), 2))) * ((2 * m1) / (m1 + m2));

        moveable1->velocity = newV1;
        moveable2->velocity = newV2;
        std::cout << "Asteroid collision: " << overlap << std::endl;
        // https://en.wikipedia.org/wiki/Elastic_collision

    }

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
