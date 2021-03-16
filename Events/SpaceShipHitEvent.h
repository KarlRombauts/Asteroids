#ifndef UNTITLED_SPACESHIPHITEVENT_H
#define UNTITLED_SPACESHIPHITEVENT_H


struct SpaceShipHitEvent {
    SpaceShipHitEvent(Entity *spaceShip, Entity *hitter)
            : spaceShip(spaceShip), hitter(hitter) {}

    Entity *spaceShip;
    Entity *hitter;
};


#endif //UNTITLED_SPACESHIPHITEVENT_H
