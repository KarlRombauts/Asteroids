//
// Created by Karl Rombauts on 19/3/21.
//

#ifndef UNTITLED_DRAGSYSTEM_H
#define UNTITLED_DRAGSYSTEM_H


#include "System.h"
#include "../Vec2.h"

class DragSystem: public System {
private:
    bool prevLeftMouseDown;
    bool prevRightMouseDown;
    Entity * selectedEntity;
    Vec2 force;
public:
    DragSystem();

    void update(EntityManager &entities, double dt) override;
};


#endif //UNTITLED_DRAGSYSTEM_H
