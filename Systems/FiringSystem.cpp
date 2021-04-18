#include <GLUT/glut.h>
#include "FiringSystem.h"
#include "../Components/FiringBullet.h"
#include "../Components/SpaceShip.h"
#include "../Components/Transform.h"
#include "../Components/Kinematics.h"
#include "../Components/Bullet.h"
#include "../Components/Collision.h"
#include "../Components/Texture.h"
#include "../Components/Damage.h"
#include "../Components/Particle.h"

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

            Vec2 bulletVelocity = entity->get<Kinematics>()->velocity + Vec2::polar(transform->rotation, 100);
            bullet->assign<Transform>(transform->position, transform->rotation, Vec2(1, 1));
            bullet->assign<Kinematics>(bulletVelocity, Vec2(0, 0), 1);
            bullet->assign<Bullet>(10);
            bullet->assign<Particle>();
            bullet->assign<Damage>(20);
            bullet->assign<Collision>(CollisionType::TRIGGER);
            bullet->assign<CircleCollision>(2);
            bullet->assign<Texture>(1, 1, 0);
        }
    }
}
