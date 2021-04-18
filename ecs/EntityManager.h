//
// Created by Karl Rombauts on 13/3/21.
//

#ifndef UNTITLED_ENTITYMANAGER_H
#define UNTITLED_ENTITYMANAGER_H


#include <unordered_map>
#include <vector>
#include "Entity.h"
#include "../Vec2.h"
#include "../TextAlignment.h"

class EntityManager {
private:
    unsigned int nextId;
    std::unordered_map<unsigned int, Entity*> entities;
public:
    Entity * create();

    Entity * createAsteroid(double radius);

    void destroy(Entity *entity);

    template<typename... Components>
    Entity *getFirstEntityWith();

    template<typename ... Components>
    std::vector<Entity*> getEntitiesWith();

    Entity *createFixedLine(Vec2 start, Vec2 end);

    void createArena();

    Entity *createSpaceShip(Vec2 position);

    Entity *createBullet(Vec2 position, Vec2 velocity);

    Entity *createBoundingCircle(double radius);

    Entity *createBlackHole(double radius, Vec2 position);

    void destroyAll();

    void createWorld();

};

template<typename... Components>
std::vector<Entity*> EntityManager::getEntitiesWith() {
    std::vector<Entity*> result;

    for (auto entity: entities) {
        if (entity.second->has<Components...>()) {
           result.push_back(entity.second);
        }
    }

    return result;
}

template<typename... Components>
Entity* EntityManager::getFirstEntityWith() {
    std::vector<Entity*> result;

    for (auto entity: entities) {
        if (entity.second->has<Components...>()) {
            return entity.second;
        }
    }

    return nullptr;
}


#endif //UNTITLED_ENTITYMANAGER_H
