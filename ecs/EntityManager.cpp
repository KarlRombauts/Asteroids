#include "EntityManager.h"
#include "Entity.h"
#include "../Components/Transform.h"
#include "../Components/Collision.h"
#include "../Components/Texture.h"
#include "../Components/Moveable.h"
#include "../Components/Asteroid.h"
#include "../Components/Helpers.h"
#include "../Components/Shape.h"
#include "../GameState.h"
#include "../Components/Draggable.h"
#include "../Components/Health.h"
#include "../Components/HealthBar.h"
#include "../Components/SplitOnDeath.h"
#include "../Components/Wall.h"
#include "../Components/Child.h"
#include "../Components/BoundingCircle.h"
#include "../Components/PlayerInput.h"
#include "../Components/SpaceShip.h"


Entity *EntityManager::create() {
    unsigned int id = nextId;
    entities.insert(std::make_pair<int, Entity *>(nextId, new Entity(id)));
    nextId++;
    return entities.at(id);
}


Entity *EntityManager::createAsteroid(double radius) {
    Entity *asteroid = this->create();
    const CoordinateSpace &world = gameState.getWorldCoordinates();

    asteroid->assign<Transform>(
            Vec2(randf(world.minX, world.maxX), randf(world.minY, world.maxY)),
            0, Vec2(1, 1));

    std::vector<Vec2> asteroidModel;
    int num_segments = 10;
    double roughness = 0.2;
    for (int i = 0; i < num_segments; i++) {
        double theta = 2.0 * M_PI * float(i) /
                       float(num_segments); // get the current angle

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
    asteroid->assign<Draggable>(radius);
    asteroid->assign<Texture>(1, 1, 1);
    asteroid->assign<Health>(radius * 10);
    asteroid->assign<HealthBar>();

    Moveable moveable(Vec2::polar(randf(0, 360), randf(10, 20)), Vec2(0, 0), pow(radius, 2));
    moveable.angularVelocity = randf(-180, 180);

    asteroid->assign<Moveable>(moveable);

    if (radius > 2) {
        asteroid->assign<SplitOnDeath>();
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
    int l = gameState.arenaSize;
    Entity *leftWall = createFixedLine(Vec2(-l, -l), Vec2(-l, l));
    leftWall->assign<Wall>();

    Entity *topWall = createFixedLine(Vec2(-l, l), Vec2(l, l));
    topWall->assign<Wall>();

    Entity *rightWall = createFixedLine(Vec2(l, -l), Vec2(l, l));
    rightWall->assign<Wall>();

    Entity *bottomWall = createFixedLine(Vec2(-l, -l), Vec2(l, -l));
    bottomWall->assign<Wall>();
}

Entity *EntityManager::createSpaceShip() {
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
    spaceShip->assign<SpaceShip>(200, 50);
    spaceShip->assign<Collision>(CollisionType::DYNAMIC);
    spaceShip->assign<CircleCollision>(5);

    spaceShip->assign<Texture>(1, 0, 0);
    spaceShip->assign<Transform>(Vec2(0, 0), 90, Vec2(1, 1));
    spaceShip->assign<Moveable>(Vec2(0, 0), Vec2(0, 0), 1);
    spaceShip->get<Moveable>()->drag = 1;

    spaceShip->assign<PlayerInput>();

    Entity *boundingCircle = createBoundingCircle(30);
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
    // TODO: Fix memory leak
    entities.erase(entity->getId());
}
