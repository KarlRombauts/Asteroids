//
// Created by Karl Rombauts on 17/4/21.
//

#include "ParticleSystem.h"
#include "../Components/ParticleSource.h"
#include "../Components/Transform.h"
#include "../Components/Particle.h"
#include "../Components/Texture.h"
#include "../Components/Moveable.h"
#include "../Components/Helpers.h"

void ParticleSystem::update(EntityManager &entities, double dt) {
    for (Entity *emitter: entities.getEntitiesWith<ParticleSource, Transform>()) {
        ParticleSource *particleSource = emitter->get<ParticleSource>();

        if (!particleSource->started) {
            for (int i = 0; i < particleSource->initialParticles; i++) {
                emitParticle(entities, emitter);
            }
            particleSource->started = true;
        }

        particleSource->timeSinceLastParticle += dt;
        int numParticles = (particleSource->spawnRate / (float) 1000) * particleSource->timeSinceLastParticle;

        for (int i = 0; i < numParticles; i++) {
            emitParticle(entities, emitter);
        }

        particleSource->timeSinceLastParticle -= ((double) numParticles * 1000 / (double) particleSource->spawnRate);
    }


    for (Entity* particle: entities.getEntitiesWith<Particle>()) {
        Texture *texture = particle->get<Texture>();
        double decayRate = 1 * dt / 1000;
        texture->red = lerp(texture->red, 0, decayRate);
        texture->green = lerp(texture->green, 0, decayRate);
        texture->blue = lerp(texture->blue, 0, decayRate);

        if (texture->red + texture->blue + texture->green < 0.1) {
            entities.destroy(particle);
        }
    }
}

void
ParticleSystem::emitParticle(EntityManager &entities, Entity *emitterEntity) const {
    ParticleSource *particleSource = emitterEntity->get<ParticleSource>();
    Entity* particle = entities.create();
    particle->assign<Particle>();
    particle->assign<Transform>(*emitterEntity->get<Transform>());

    double d = particleSource->dispersion;
    Vec2 velocity = Vec2::polar(randf(0, 360), d + randf(-d / 3, d / 3)) + particleSource->velocity;
    particle->assign<Moveable>(velocity, Vec2(0,0), 0);
    particle->assign<Texture>(1, 1, 1);
}
