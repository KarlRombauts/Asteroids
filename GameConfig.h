#ifndef UNTITLED_GAMECONFIG_H
#define UNTITLED_GAMECONFIG_H

#include "Components/Texture.h"

struct GameConfig {
    // Player Config
    char PLAYER_FORWARD = 'w';
    char PLAYER_LEFT = 'a';
    char PLAYER_RIGHT = 'd';
    char PLAYER_SHOOT = ' ';
    double PLAYER_SPEED = 75;
    double PLAYER_TURN_SPEED = 180; // Degrees per second

    int PLAYER_FIRING_RATE = 200; // Bullets per second
    double BULLET_SPEED = 10;

    int EXHAUST_PARTICLE_RATE = 10;
    int EXHAUST_PARTICLE_DECAY = 10;

    double WARNING_DISTANCE = 20; // Game world units


    // Asteroid Config
    double ASTEROID_MAX_SPEED = 20;
    double ASTEROID_MIN_SPEED = 20;

    double ASTEROID_MAX_ROTATION = 20; // Degrees per second
    double ASTEROID_MIN_ROTATION = 20; // Degrees per second

    int ASTEROID_MIN_START_RADIUS = 8;
    int ASTEROID_MAX_START_RADIUS = 32;

    Texture ASTEROID_COLOR = {1, 1, 1};


    // Wave Config
    double TIME_BETWEEN_WAVE = 10; // Seconds

    double BLACK_HOLE_PULSE_RATE = 0.5; // times per second;
    Texture BLACK_HOLE_COLOR = {0.5, 0.5, 0.5};
};


#endif //UNTITLED_GAMECONFIG_H
