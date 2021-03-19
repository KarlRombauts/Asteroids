//
// Created by Karl Rombauts on 16/3/21.
//

#include <GLUT/glut.h>
#include "FiringSystem.h"
#include "../Components/FiringBullet.h"
#include "../Components/SpaceShip.h"
#include "../Components/Transform.h"
#include "../Components/Moveable.h"
#include "../Components/Bullet.h"
#include "../Components/Collision.h"
#include "../Components/Texture.h"

void FiringSystem::update(EntityManager &entities, double dt) {
    for (Entity *entity: entities.getEntitiesWith<SpaceShip, FiringBullet>()) {
        SpaceShip* spaceShip = entity->get<SpaceShip>();

        int thisTime = glutGet(GLUT_ELAPSED_TIME);
        int timeSinceLastFire = thisTime - spaceShip->lastFire;

        if (timeSinceLastFire > spaceShip->fireRate) {
            spaceShip->lastFire = thisTime;
            entity->remove<FiringBullet>();
            Entity *bullet = entities.create();

            Transform *transform = entity->get<Transform>();

            bullet->assign<Transform>(transform->position, transform->rotation, Vec2(1, 1), OutOfBoundsBehaviour::DESTROY);
            Vec2 bulletVelocity = entity->get<Moveable>()->velocity + Vec2::polar(transform->rotation, 100);
            bullet->assign<Moveable>(bulletVelocity, Vec2(0,0), 1);
            bullet->assign<Bullet>(10);
            bullet->assign<Collision>(CollisionType::TRIGGER, 2);
            bullet->assign<Texture>(1, 1, 0);
        }
    }
}
