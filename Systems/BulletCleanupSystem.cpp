//
// Created by Karl Rombauts on 10/4/21.
//

#include "BulletCleanupSystem.h"
#include "../Components/Impact.h"
#include "../Components/Bullet.h"
#include "../Components/Collision.h"
#include "../Components/SpaceShip.h"

void BulletCleanupSystem::update(EntityManager &entities, double dt) {
    for (Entity *entity: entities.getEntitiesWith<Impact, Bullet>()) {
        std::vector<Entity *> otherEntities = entity->get<Impact>()->entities;

        for (Entity *otherEntity: otherEntities) {
            if (otherEntity->has<SpaceShip>()) {
                continue;
            }
            if (otherEntity->get<Collision>()->type == CollisionType::TRIGGER) {
                continue;
            }
            entities.destroy(entity);
            return;
        }
    }
}
