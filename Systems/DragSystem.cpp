//
// Created by Karl Rombauts on 19/3/21.
//

#include "DragSystem.h"
#include "../Components/Draggable.h"
#include "../Globals.h"
#include "../Components/Transform.h"
#include "../Components/Kinematics.h"

void DragSystem::update(EntityManager &entities, double dt) {
    if (mouseState.leftMouseDown) {
        for (Entity * entity: entities.getEntitiesWith<Draggable, Transform, Kinematics>()) {
            Draggable * draggable = entity->get<Draggable>();
            Transform * transform = entity->get<Transform>();
            Kinematics * kinematics = entity->get<Kinematics>();
            Vec2 offset = mouseState.drag - transform->position;
            if (offset.magnitude() < draggable->targetSize) {
                transform->position = mouseState.drag;
                kinematics->velocity = {0,0};

            }
        }
    }
    if (mouseState.rightMouseDown && !prevRightMouseDown) {
        // Click
        for (Entity * entity: entities.getEntitiesWith<Draggable, Transform, Kinematics>()) {
            Draggable * draggable = entity->get<Draggable>();
            Transform * transform = entity->get<Transform>();
            Vec2 offset = mouseState.drag - transform->position;
            if (offset.magnitude() < draggable->targetSize) {
                selectedEntity = entity;
            }
        }
    }

    if (mouseState.rightMouseDown && prevRightMouseDown) {
        // Drag
        if (selectedEntity != nullptr) {
            Transform * transform = selectedEntity->get<Transform>();
            force = (mouseState.drag - transform->position) * 100 ;
        }
    }

    if (!mouseState.rightMouseDown && prevRightMouseDown) {
        // Release
        if (selectedEntity != nullptr) {
            selectedEntity->get<Kinematics>()->acceleration += force;
        }
    }

    prevLeftMouseDown = mouseState.leftMouseDown;
    prevRightMouseDown = mouseState.rightMouseDown;
}

DragSystem::DragSystem() : prevLeftMouseDown(false),
          prevRightMouseDown(false),
          selectedEntity(nullptr), force({0,0}) {}
