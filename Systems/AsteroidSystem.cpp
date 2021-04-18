#include "AsteroidSystem.h"
#include "../Globals.h"

void AsteroidSystem::startWave(EntityManager &entities, int waveCount) {
    Entity *spaceShip = entities.getFirstEntityWith<SpaceShip>();

    for (int i = 0; i < waveCount; i++) {
        launchAsteroidAtSpaceShip(entities, spaceShip);
    }
}

void AsteroidSystem::launchAsteroidAtSpaceShip(EntityManager &entities, Entity *spaceShip) const {
    int radius = randInt(gameConfig.ASTEROID_MIN_START_RADIUS, gameConfig.ASTEROID_MAX_START_RADIUS);
    Entity *asteroid = entities.createAsteroid(radius);
    Vec2 asteroidPosition = Vec2::polar(randf(0, 360), gameState.worldCoordinates.distanceToCorner());
    asteroid->get<Transform>()->position = asteroidPosition;
    asteroid->assign<OutsideArena>();

    if (spaceShip) {
        Vec2 spaceShipPosition = spaceShip->get<Transform>()->position;
        double speed = randf(gameConfig.ASTEROID_MIN_SPEED, gameConfig.ASTEROID_MAX_SPEED);
        const Vec2 velocity = (spaceShipPosition - asteroidPosition).normalize().scale(speed);
        asteroid->get<Kinematics>()->velocity = velocity;
    }
}

void update(EntityManager &entities) {
}