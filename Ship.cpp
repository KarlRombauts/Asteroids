//
// Created by Karl Rombauts on 12/3/21.
//

#include <cmath>
#include "OpenGL.h"
#include "Ship.h"
#include "Globals.h"
#include "GameState.h"


void Ship::update(double dt) {
    if (keyboardState.isKeyPressed('a'))
        this->rotation += (float) dt * 0.1f;
    if (keyboardState.isKeyPressed('d'))
        this->rotation -= (float) dt * 0.1f;
    if (keyboardState.isKeyPressed('w')) {
        Vec2 a = Vec2::polar(rotation, 2);
        this->velocity = this->velocity + a * dt;
    }

    this->position = this->position + this->velocity * dt;

    CoordinateSpace world = gameState.getWorldCoordinates();
}

void Ship::render() {
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslatef(this->position.x, this->position.y, 0);
        glRotatef(this->rotation, 0, 0, 1);
        glBegin(GL_POLYGON);
        {
            glVertex3f(-0.1, -0.1, 0);
            glVertex3f(0.1, 0, 0);
            glVertex3f(-0.1, 0.1, 0);
        }
        glEnd();
    glPopMatrix();
}

Ship::Ship(Vec2 position, float rotation, double maxSpeed, float mass):
    position(position),
    velocity(0, 0),
    rotation(rotation),
    maxSpeed(maxSpeed),
    mass(mass) {}
