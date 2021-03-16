//
// Created by Karl Rombauts on 13/3/21.
//

#include "Entity.h"

Entity::Entity(unsigned int id)
        : id(id), components(std::unordered_map<std::type_index, Component *>()) {}

unsigned int Entity::getId() {
    return id;
}

