#include "ShipImpactSystem.h"
#include "../Components/SpaceShip.h"
#include "../Components/Impact.h"
#include "../Components/Asteroid.h"
#include "../Components/Wall.h"

void ShipImpactSystem::update(EntityManager &entities) {
    for (Entity *spaceShip: entities.getEntitiesWith<SpaceShip, Impact>()) {
        for (Entity *otherEntity: spaceShip->get<Impact>()->entities) {
            if (otherEntity->hasAny<Asteroid, Wall>()) {
               entities.destroy(spaceShip);
            }
        }
    }
}
