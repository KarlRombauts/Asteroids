//
// Created by Karl Rombauts on 16/3/21.
//

#ifndef UNTITLED_SHAPE_H
#define UNTITLED_SHAPE_H


#include <utility>
#include <vector>
#include "../ecs/Component.h"
#include "../Vec2.h"

struct Shape: public Component {
    Shape(std::vector<Vec2> vertices) : vertices(std::move(vertices)){}

    std::vector<Vec2> vertices;
};


#endif //UNTITLED_SHAPE_H
