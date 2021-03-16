//
// Created by Karl Rombauts on 13/3/21.
//

#ifndef UNTITLED_ENTITYMANAGER_H
#define UNTITLED_ENTITYMANAGER_H


#include <unordered_map>
#include <vector>
#include "Entity.h"

class EntityManager {
private:
    unsigned int nextId;
    std::unordered_map<unsigned int, Entity*> entities;
public:
    Entity * create();

    Entity * createAsteroid(double radius);

    void destroy(Entity *entity);

    template<typename ... Components>
    std::vector<Entity*> getEntitiesWith();
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



#endif //UNTITLED_ENTITYMANAGER_H
