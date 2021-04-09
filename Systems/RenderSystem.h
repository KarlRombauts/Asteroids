//
// Created by Karl Rombauts on 14/3/21.
//

#ifndef UNTITLED_RENDERSYSTEM_H
#define UNTITLED_RENDERSYSTEM_H


#include "System.h"

class RenderSystem: public System {

public:
    void update(EntityManager &entities, double dt) override;
};


#endif //UNTITLED_RENDERSYSTEM_H
