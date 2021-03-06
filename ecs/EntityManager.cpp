#include "EntityManager.h"
#include "Entity.h"
#include "../Components/Transform.h"
#include "../Components/Collision.h"
#include "../Components/Texture.h"
#include "../Components/Kinematics.h"
#include "../Components/Asteroid.h"
#include "../Helpers.h"
#include "../Components/Shape.h"
#include "../GameModel.h"
#include "../Components/Health.h"
#include "../Components/HealthBar.h"
#include "../Components/SplitOnDeath.h"
#include "../Components/Wall.h"
#include "../Components/Child.h"
#include "../Components/BoundingCircle.h"
#include "../Components/PlayerInput.h"
#include "../Components/SpaceShip.h"
#include "../Components/BlackHole.h"
#include "../Components/GravityForce.h"
#include "../Globals.h"
#include "../Components/Particle.h"
#include "../Components/Bullet.h"
#include "../Components/Damage.h"


Entity *EntityManager::create() {
    unsigned int id = nextId;
    entities.insert(std::make_pair<int, Entity *>(nextId, new Entity(id)));
    nextId++;
    return entities.at(id);
}

Entity *EntityManager::createBlackHole(double radius, Vec2 position) {
    std::vector<Vec2> circle;
    int num_segments = 16;
    for (int i = 0; i < num_segments; i++) {
        double theta = 2.0 * M_PI * float(i) / float(num_segments); // get the current angle

        double x = radius * cos(theta); // calculate the x component
        double y = radius * sin(theta); // calculate the y component

        Vec2 vertex = {x, y};

        circle.push_back(vertex);
    }

    Entity* blackHole = create();
    blackHole->assign<Transform>(position, 0, Vec2(1, 1));
    blackHole->assign<Shape>(circle);
    blackHole->assign<BlackHole>();
    blackHole->assign<Collision>(CollisionType::TRIGGER);
    blackHole->assign<CircleCollision>(radius / 4);
    blackHole->assign<GravityForce>(gameConfig.BLACK_HOLE_STRENGTH);
    blackHole->assign<Texture>(gameConfig.BLACK_HOLE_COLOR);
    return blackHole;
}

Entity *EntityManager::createAsteroid(double radius) {
    Entity *asteroid = this->create();
    const CoordinateSpace &world = gameModel.worldCoordinates;

    asteroid->assign<Transform>(
            Vec2(randf(world.minX, world.maxX), randf(world.minY, world.maxY)),
            0, Vec2(1, 1));

    std::vector<Vec2> asteroidModel;
    int num_segments = 12;
    double roughness = 0.2;
    for (int i = 0; i < num_segments; i++) {
        double theta = 2.0 * M_PI * float(i) / float(num_segments); // get the current angle
        double x = radius * cos(theta); // calculate the x component
        double y = radius * sin(theta); // calculate the y component

        Vec2 vertex = {
            x + radius * randf(-roughness, roughness),
            y + radius * randf(-roughness, roughness)
        };

        asteroidModel.push_back(vertex);
    }

    asteroid->assign<Asteroid>(radius);
    asteroid->assign<Shape>(asteroidModel);
    asteroid->assign<Collision>(CollisionType::DYNAMIC);
    asteroid->assign<CircleCollision>(radius);
    asteroid->assign<Texture>(gameConfig.ASTEROID_COLOR);
    asteroid->assign<Health>(radius * 10);

    Kinematics kinematics(Vec2::polar(randf(0, 360), randf(10, 20)), Vec2(0, 0), pow(radius, 2));
    kinematics.angularVelocity = randf(gameConfig.ASTEROID_MIN_ROTATION, gameConfig.ASTEROID_MAX_ROTATION);

    asteroid->assign<Kinematics>(kinematics);

    if (radius > 2) {
        asteroid->assign<SplitOnDeath>();
        asteroid->assign<HealthBar>();
    }

    return asteroid;
}

Entity *EntityManager::createFixedLine(Vec2 start, Vec2 end) {
    Entity *line = create();
    line->assign<Line>(start, end);
    line->assign<Collision>(CollisionType::STATIC);
    line->assign<LineCollision>(line->get<Line>());
    line->assign<Transform>();
    line->assign<Texture>(1, 1, 1);
    return line;
}

void EntityManager::createArena() {
    int l = gameModel.arenaSize;
    Entity *leftWall = createFixedLine(Vec2(-l, -l), Vec2(-l, l));
    leftWall->assign<Wall>();

    Entity *topWall = createFixedLine(Vec2(-l, l), Vec2(l, l));
    topWall->assign<Wall>();

    Entity *rightWall = createFixedLine(Vec2(l, -l), Vec2(l, l));
    rightWall->assign<Wall>();

    Entity *bottomWall = createFixedLine(Vec2(-l, -l), Vec2(l, -l));
    bottomWall->assign<Wall>();
}

Entity *EntityManager::createSpaceShip(Vec2 position) {
    Entity *spaceShip = create();

    std::vector<Vec2> spaceShipModel = {
            {4,  0},
            {-3, 0},
            {-4, 2},
            {4,  0},
            {-3, 0},
            {-4, -2}
    };

    spaceShip->assign<Shape>(spaceShipModel);
    spaceShip->assign<SpaceShip>(gameConfig.PLAYER_FIRING_RATE, gameConfig.PLAYER_SPEED);
    spaceShip->assign<Collision>(CollisionType::DYNAMIC);
    spaceShip->assign<CircleCollision>(5);

    spaceShip->assign<Texture>(1, 0, 0);
    spaceShip->assign<Transform>(position, 90, Vec2(1, 1));
    spaceShip->assign<Kinematics>(Vec2(0, 0), Vec2(0, 0), 1);
    spaceShip->get<Kinematics>()->drag = 1;

    spaceShip->assign<PlayerInput>();

    Entity *boundingCircle = createBoundingCircle(gameConfig.WARNING_DISTANCE);
    spaceShip->assign<Child>(boundingCircle);
    return spaceShip;
}

Entity *EntityManager::createBoundingCircle(double radius) {
    Entity *boundingCircle = create();
    boundingCircle->assign<BoundingCircle>();
    boundingCircle->assign<Collision>(CollisionType::TRIGGER);
    boundingCircle->assign<CircleCollision>(radius);
    boundingCircle->assign<Transform>(Vec2(0, 0), 90, Vec2(1, 1));
    return boundingCircle;
}

void EntityManager::destroy(Entity *entity) {
    entities.erase(entity->getId());
    delete entity;
}

void EntityManager::createWorld() {
    createArena();
    const Vec2 shipPosition = Vec2(gameModel.arenaSize * -0.7, gameModel.arenaSize * -0.7);
    createSpaceShip(shipPosition);

    if (gameModel.difficulty == Difficulty::HARD) {
        // Never create a black hole that is too close to the ship
        int range = gameModel.arenaSize * 0.8;
        Vec2 blackHolePosition = Vec2(0,0);
        do {
            blackHolePosition = Vec2(randInt(-range, range),
                                     randInt(-range, range));
        } while((blackHolePosition - shipPosition).magnitude() < gameModel.arenaSize * 0.4);

        createBlackHole(10, blackHolePosition);
    }
}

void EntityManager::destroyAll() {
    for (std::pair<const unsigned int, Entity *> entity: entities) {
        delete entity.second;
    }
    entities.clear();
}

Entity *EntityManager::createBullet(Vec2 position, Vec2 velocity) {
    Entity *bullet = create();
    bullet->assign<Transform>(position, 0, Vec2(1, 1));
    bullet->assign<Kinematics>(velocity, Vec2(0, 0), 1);
    bullet->assign<Particle>();
    bullet->assign<Bullet>();
    bullet->assign<Damage>(gameConfig.BULLET_DAMAGE);
    bullet->assign<Collision>(CollisionType::TRIGGER);
    bullet->assign<CircleCollision>(2);
    bullet->assign<Texture>(gameConfig.BULLET_COLOR);
    return bullet;
}

