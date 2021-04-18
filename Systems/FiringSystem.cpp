#include <GLUT/glut.h>
#include "FiringSystem.h"
#include "../Components/FiringBullet.h"
#include "../Components/SpaceShip.h"
#include "../Components/Transform.h"
#include "../Components/Kinematics.h"
#include "../Components/Texture.h"
#include "../Globals.h"

void FiringSystem::update(EntityManager &entities, double dt) {
    for (Entity *entity: entities.getEntitiesWith<SpaceShip, FiringBullet>()) {
        SpaceShip* spaceShip = entity->get<SpaceShip>();

        int thisTime = glutGet(GLUT_ELAPSED_TIME);
        int timeSinceLastFire = thisTime - spaceShip->lastFire;

        if (timeSinceLastFire > spaceShip->fireRate) {
            spaceShip->lastFire = thisTime;
            entity->remove<FiringBullet>();

            Transform *transform = entity->get<Transform>();
            Vec2 bulletVelocity = entity->get<Kinematics>()->velocity + Vec2::polar(transform->rotation, gameConfig.BULLET_SPEED);

            entities.createBullet(transform->position, bulletVelocity);
        }
    }
}
