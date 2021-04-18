#include "BlackHoleSystem.h"
#include "../Components/BlackHole.h"
#include "../Components/Transform.h"
#include "../GameState.h"
#include "../Components/Impact.h"
#include "../Components/Collision.h"
#include "../Components/Destroy.h"
#include "../Components/BoundingCircle.h"

void BlackHoleSystem::update(EntityManager &entities, double dt) {
    for (Entity *entity: entities.getEntitiesWith<BlackHole, Transform, CircleCollision>()) {
        Transform* transform = entity->get<Transform>();

        double pulseTime = 2;
        double minSize = 0.7;
        double scale = (1 - ((fmod(gameState.msElapsedTime / (double) 1000, pulseTime)) / pulseTime) + minSize) / (1 + minSize);

        transform->scale = Vec2(scale, scale);
    }

    for (Entity *blackHole: entities.getEntitiesWith<BlackHole, Impact>()) {
        for (Entity *otherEntity: blackHole->get<Impact>()->entities) {
            if (!otherEntity->has<BoundingCircle>()) {
                otherEntity->assign<Destroy>();
            }
        }
    }
}
