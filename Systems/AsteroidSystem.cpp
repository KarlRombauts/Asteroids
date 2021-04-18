#include "AsteroidSystem.h"

void AsteroidSystem::startWave(EntityManager &entities, int waveCount) {
    Entity *spaceShip = entities.getFirstEntityWith<SpaceShip>();

    for (int i = 0; i < waveCount; i++) {
        launchAsteroidAtSpaceShip(entities, spaceShip);
    }
}

void AsteroidSystem::launchAsteroidAtSpaceShip(EntityManager &entities, Entity *spaceShip) const {
    Entity *asteroid = entities.createAsteroid(8);
    Vec2 asteroidPosition = Vec2::polar(randf(0, 360), gameState.worldCoordinates.distanceToCorner());
    asteroid->get<Transform>()->position = asteroidPosition;
    asteroid->assign<OutsideArena>();

    if (spaceShip) {
        Vec2 spaceShipPosition = spaceShip->get<Transform>()->position;
        const Vec2 &asteroidSpeed = (spaceShipPosition - asteroidPosition).normalize().scale(10);
        asteroid->get<Kinematics>()->velocity = asteroidSpeed;
    }
}

void update(EntityManager &entities) {
}