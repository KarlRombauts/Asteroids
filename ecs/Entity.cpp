//
// Created by Karl Rombauts on 13/3/21.
//

#include "Entity.h"

Entity::Entity(unsigned int i)
        : components(std::unordered_map<std::type_index, Component *>()) {}
