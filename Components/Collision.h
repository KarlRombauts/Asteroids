//
// Created by Karl Rombauts on 15/3/21.
//

#ifndef UNTITLED_COLLISION_H
#define UNTITLED_COLLISION_H

#import <deque>

enum class CollisionType {
    STATIC,
    DYNAMIC,
    TRIGGER
};

struct Collision: public Component {
    Collision(CollisionType type, double radius) : type(type), radius(radius) {}
    CollisionType type;
    double radius;
};


#endif //UNTITLED_COLLISION_H
