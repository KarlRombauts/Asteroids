#include <iostream>
#include "DamageSystem.h"
#include "../Components/Impact.h"
#include "../Components/Damage.h"
#include "../Components/Health.h"
#include "../Components/Destroy.h"
#include "../Components/SplitOnDeath.h"
#include "../Components/Asteroid.h"
#include "../Components/Transform.h"
#include "../Components/Collision.h"
#include "../Components/Moveable.h"

void DamageSystem::update(EntityManager &entities) {
    for(Entity* entity: entities.getEntitiesWith<Impact, Health>()) {
        Health *health = entity->get<Health>();

        for (Entity* otherEntity: entity->get<Impact>()->entities) {
            if (otherEntity->has<Damage>()) {
               health->health -= otherEntity->get<Damage>()->damage;
            }
            if (health->health <= 0) {
                handleDeath(entities, entity, otherEntity);
                break;
            }
        }

    }
}

void DamageSystem::handleDeath(EntityManager &entities, Entity *entity, Entity *otherEntity) const {

    std::cout << "kill entity" << std::endl;
    entity->remove<Collision>();
    if (entity->has<SplitOnDeath>()) {
        if (entity->has<Asteroid, Transform>()) {
            double size = entity->get<Asteroid>()->size;
            Vec2 p1 = entity->get<Transform>()->position;
            Vec2 p2 = otherEntity->get<Transform>()->position;
            Vec2 v = entity->get<Moveable>()->velocity;

            Vec2 splitDir = (p2 - p1).perpendicular() * size / 2;

            if (size >= 2) {
                Entity *asteroid1 = entities.createAsteroid(size / 2);
                Entity *asteroid2 = entities.createAsteroid(size / 2);

                asteroid1->get<Transform>()->position = p1 + splitDir;
                asteroid1->get<Moveable>()->velocity = (p2 - p1).normalize().scale(v.magnitude()).rotate(25);
                asteroid2->get<Transform>()->position = p1 - splitDir;
                asteroid1->get<Moveable>()->velocity = (p2 - p1).normalize().scale(v.magnitude()).rotate(-25);
            }
        }
    }
    entities.destroy(entity);
}