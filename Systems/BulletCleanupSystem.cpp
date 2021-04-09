//
// Created by Karl Rombauts on 10/4/21.
//

#include "BulletCleanupSystem.h"
#include "../Components/Impact.h"
#include "../Components/Bullet.h"

void BulletCleanupSystem::update(EntityManager &entities, double dt) {
    for (Entity *entity: entities.getEntitiesWith<Impact, Bullet>()) {
        entities.destroy(entity);
    }
}
