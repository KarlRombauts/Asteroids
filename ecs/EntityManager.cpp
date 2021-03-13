//
// Created by Karl Rombauts on 13/3/21.
//

#include "EntityManager.h"

Entity * EntityManager::create() {
    unsigned int id = nextId;
    entities.insert(std::make_pair<int, Entity*>(nextId, new Entity(id)));
    nextId++;
    return entities.at(id);
}
