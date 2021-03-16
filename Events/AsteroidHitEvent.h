//
// Created by Karl Rombauts on 14/3/21.
//

#ifndef UNTITLED_ASTEROIDHITEVENT_H
#define UNTITLED_ASTEROIDHITEVENT_H


struct AsteroidHitEvent {
    AsteroidHitEvent(Entity *asteroid, Entity *hitter)
        : asteroid(asteroid), hitter(hitter) {}

    Entity* asteroid;
    Entity* hitter;
};


#endif //UNTITLED_ASTEROIDHITEVENT_H
