//
// Created by Karl Rombauts on 16/4/21.
//

#ifndef UNTITLED_PARTICLESOURCE_H
#define UNTITLED_PARTICLESOURCE_H


struct ParticleSource: public Component {
    ParticleSource(Vec2 velocity, double dispersion, int initialParticles, int spawnRate)
                   : velocity(velocity), dispersion(dispersion), initialParticles(initialParticles), spawnRate(spawnRate) {}

    double dispersion;
    Vec2 velocity;
    int initialParticles;
    int spawnRate;
    double timeSinceLastParticle = 0;
    bool started = false;
};


#endif //UNTITLED_PARTICLESOURCE_H
