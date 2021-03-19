#include <OpenGL/OpenGL.h>
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

Entity * EntityManager::create() {
    unsigned int id = nextId;
    entities.insert(std::make_pair<int, Entity*>(nextId, new Entity(id)));
    nextId++;
    return entities.at(id);
}

Entity* EntityManager::createAsteroid(double radius) {
    Entity *asteroid = this->create();
    const CoordinateSpace &world = gameState.getWorldCoordinates();

    asteroid->assign<Transform>(
            Vec2(randf(world.minX, world.maxX), randf(world.minY, world.maxY)),
            0, Vec2(1, 1), OutOfBoundsBehaviour::BOUNCE);

    std::vector<Vec2> asteroidModel;
    int num_segments = 10;
    double roughness = 0.2;
    for(int i = 0; i < num_segments; i++)
    {
        double theta = 2.0 * M_PI * float(i) / float(num_segments); //get the current angle

        double x = radius * cos(theta); //calculate the x component
        double y = radius * sin(theta); //calculate the y component

        Vec2 vertex = {
            x + radius * randf(-roughness, roughness),
            y + radius * randf(-roughness, roughness)
        };

       asteroidModel.push_back(vertex);
    }

    asteroid->assign<Asteroid>(radius);
    asteroid->assign<Shape>(asteroidModel);
    asteroid->assign<Collision>(CollisionType::DYNAMIC, radius);
    asteroid->assign<Draggable>(radius);
    asteroid->assign<Texture>(1, 1, 1);
    asteroid->assign<Moveable>(Vec2::polar(randf(0, 360), randf(10, 20)), Vec2(0, 0), pow(radius, 2));

    return asteroid;
}

void EntityManager::destroy(Entity *entity) {
    // TODO: Fix memory leak
    entities.erase(entity->getId());
}
