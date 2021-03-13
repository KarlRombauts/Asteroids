//
// Created by Karl Rombauts on 14/3/21.
//

#include "PlayerInputSystem.h"
#include "../Globals.h"
#include "../Components/PlayerInput.h"
#include "../Components/Transform.h"
#include "../Components/Moveable.h"

void PlayerInputSystem::update(EntityManager &entities, double dt) {
    for(Entity* entity: entities.getEntitiesWith<Transform, Moveable, PlayerInput>()) {
        Transform *transform = entity->get<Transform>();
        Moveable *moveable = entity->get<Moveable>();

        if (keyboardState.isKeyPressed('a'))
            transform->rotation += (float) dt * 0.1f;
        if (keyboardState.isKeyPressed('d'))
            transform->rotation -= (float) dt * 0.1f;

        if (keyboardState.isKeyPressed('w')) {
            moveable->acceleration = Vec2::polar(transform->rotation, 2);
        } else {
            moveable->acceleration = Vec2::polar(transform->rotation, 0);
        }
    }
}
