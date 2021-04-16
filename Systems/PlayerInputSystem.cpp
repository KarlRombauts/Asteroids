#include "PlayerInputSystem.h"
#include "../Globals.h"
#include "../Components/PlayerInput.h"
#include "../Components/Transform.h"
#include "../Components/Moveable.h"
#include "../Components/Collision.h"
#include "../Components/Texture.h"
#include "../Components/Bullet.h"
#include "../Components/SpaceShip.h"
#include "../Components/FiringBullet.h"
#include "../Components/ParticleSource.h"

void PlayerInputSystem::update(EntityManager &entities, double dt) {
    for(Entity* entity: entities.getEntitiesWith<Transform, Moveable, PlayerInput, SpaceShip>()) {
        Transform *transform = entity->get<Transform>();
        Moveable *moveable = entity->get<Moveable>();
        SpaceShip *spaceShip = entity->get<SpaceShip>();

        if (keyboardState.isKeyPressed('a'))
            transform->rotation += (float) dt * 0.2;

        if (keyboardState.isKeyPressed('d'))
            transform->rotation -= (float) dt * 0.2;

        if (keyboardState.isKeyPressed('w')) {
            moveable->acceleration = Vec2::polar(transform->rotation, spaceShip->thrust);

            Entity* particles = entities.create();
            particles->assign<ParticleSource>(moveable->acceleration.scale(-1) * dt / 1000, 5, 5, 0);
            Transform particlesTransform = *transform;
            particlesTransform.position += moveable->acceleration.normalize().scale(-3);
            particles->assign<Transform>(particlesTransform);
        }

        if (keyboardState.isKeyPressed(' '))
            entity->assign<FiringBullet>();
    }
}
