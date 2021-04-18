#include <stdlib.h>
#include <stdio.h>

#if _WIN32
    # include <windows.h>
#endif

#if __APPLE__
    # include <OpenGL/gl.h>
    # include <GLUT/glut.h>

#else
    # include <GL/gl.h>
    # include <GL/glu.h>
    # include <GL/glut.h>
#endif

#include "Ship.h"
#include "Globals.h"
#include "GameState.h"
#include "ecs/Entity.h"
#include "ecs/EntityManager.h"
#include "Components/Momentum.h"
#include "Components/PlayerInput.h"
#include "Components/Rotation.h"
#include "Systems/RenderSystem.h"
#include "Components/Moveable.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/PlayerInputSystem.h"
#include "Components/Texture.h"
#include "ecs/EventManager.h"
#include "Events/CollisionEvent.h"
#include "Systems/CollisionSystem.h"
#include "Components/Identity.h"
#include "Components/Collision.h"
#include "Systems/FiringSystem.h"
#include "Components/SpaceShip.h"
#include "Components/GravityForce.h"
#include "Components/BlackHole.h"
#include "Components/Shape.h"
#include "Systems/DragSystem.h"
#include "Systems/ImpactCleanupSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/BulletCleanupSystem.h"
#include "Components/Child.h"
#include "Components/BoundingCircle.h"
#include "Components/Wall.h"
#include "Systems/WarningSystem.h"
#include "Components/Helpers.h"
#include "Components/Asteroid.h"
#include "Systems/AsteroidSystem.h"
#include "Systems/OutOfBoundsSystem.h"
#include "Systems/ShipImpactSystem.h"
#include "Components/ParticleSource.h"
#include "Systems/ParticleSystem.h"
#include "Components/Particle.h"
#include "Systems/BlackHoleSystem.h"

/* Display callback */

EntityManager entities;
RenderSystem renderSystem;
DragSystem dragSystem;
CollisionSystem collisionSystem;
PhysicsSystem physicsSystem;
PlayerInputSystem playerInputSystem;
FiringSystem firingSystem;
ImpactCleanupSystem impactCleanupSystem;
DamageSystem damageSystem;
BulletCleanupSystem bulletCleanupSystem;
WarningSystem warningSystem;
AsteroidSystem asteroidSystem;
OutOfBoundsSystem outOfBoundsSystem;
ShipImpactSystem shipImpactSystem;
ParticleSystem particleSystem;
BlackHoleSystem blackHoleSystem;


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    renderSystem.update(entities, 0);
    glutSwapBuffers();
}

void onKeyPress(unsigned char key, int x, int y) {
    keyboardState.setPressedKey(key);
    switch (key) {
        case 27:
        case 'q':
            exit(EXIT_SUCCESS);
        default:
            break;
  }
}

void onKeyRelease(unsigned char key, int x, int y) {
    keyboardState.releaseKey(key);
}

static void idle_func(void)
{
    bool gameOver = entities.getEntitiesWith<SpaceShip>().empty();

    if (gameOver) {
        if (keyboardState.isAnyKeyPressed()) {

        } else {
            return;
        }
    }

    bool waveComplete = entities.getEntitiesWith<Asteroid>().empty();

    if (waveComplete) {
        asteroidSystem.startWave(entities, gameState.waveCount++);
    }

    int thisTime;

    thisTime = glutGet(GLUT_ELAPSED_TIME);
    int dt = thisTime - gameState.msElapsedTime;

    playerInputSystem.update(entities, dt);
    dragSystem.update(entities, dt);
    firingSystem.update(entities, dt);
    collisionSystem.update(entities, dt);
    particleSystem.update(entities, dt);
    physicsSystem.update(entities, dt);
    warningSystem.update(entities);
    damageSystem.update(entities);
    bulletCleanupSystem.update(entities, dt);
    shipImpactSystem.update(entities);
    blackHoleSystem.update(entities, dt);
    impactCleanupSystem.update(entities, dt);
    outOfBoundsSystem.update(entities);

    gameState.msElapsedTime = thisTime;

    glutPostRedisplay();
}

void reshape (int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    gameState.resizeScreen(w, h);
}


void init() {
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    entities.createArena();
    entities.createSpaceShip(Vec2(0, 0));
    asteroidSystem.startWave(entities, gameState.waveCount);
    entities.createBlackHole(10, Vec2(40, 50));

}


void onMouseButton(int btn, int state, int x, int y) {
    mouseState.onMouseButton(btn, state, x, y);
}


void onMouseMove(int x, int y) {
    mouseState.onMouseMove(x, y);
}


void onMouseDrag(int x, int y) {
    mouseState.onMouseDrag(x, y);
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Asteroids");
    reshape(500, 600);
    init();

    /* Display and keyboard callbacks */
    glutIdleFunc(idle_func);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(onKeyPress);
    glutKeyboardUpFunc(onKeyRelease);
    glutMouseFunc(onMouseButton);
    glutMotionFunc(onMouseDrag);
    glutPassiveMotionFunc(onMouseMove);

    /* Let glut take over */
    glutMainLoop();
}