#include <stdlib.h>

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

#include "Globals.h"
#include "GameState.h"
#include "ecs/EntityManager.h"
#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/PlayerInputSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/FiringSystem.h"
#include "Components/SpaceShip.h"
#include "Systems/ImpactCleanupSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/BulletCleanupSystem.h"
#include "Systems/WarningSystem.h"
#include "Components/Asteroid.h"
#include "Systems/AsteroidSystem.h"
#include "Systems/OutOfBoundsSystem.h"
#include "Systems/ShipImpactSystem.h"
#include "Systems/ParticleSystem.h"
#include "Systems/BlackHoleSystem.h"
#include "Systems/DestroySystem.h"

EntityManager entities;
RenderSystem renderSystem;
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
DestroySystem destroySystem;


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    renderSystem.update(entities, 0);
    glutSwapBuffers();
}

static void idle() {
    if (gameState.isGameOver) {
        if (keyboardState.isAnyKeyPressed()) {
            entities.destroyAll();
            gameState.reset();
            entities.createWorld();
        }
    } else {
        int thisTime = glutGet(GLUT_ELAPSED_TIME);

        if (gameState.isWaveOver) {
            asteroidSystem.startWave(entities, gameState.waveCount++);
        }

        int dt = thisTime - gameState.msElapsedTime;

        playerInputSystem.update(entities, dt);
        firingSystem.update(entities, dt);
        collisionSystem.update(entities, dt);
        particleSystem.update(entities, dt);
        physicsSystem.update(entities, dt);
        warningSystem.update(entities);
        damageSystem.update(entities);
        bulletCleanupSystem.update(entities, dt);
        shipImpactSystem.update(entities);
        blackHoleSystem.update(entities, dt);
        outOfBoundsSystem.update(entities);
        impactCleanupSystem.update(entities, dt);
        destroySystem.update(entities);

        gameState.msElapsedTime = thisTime;
        gameState.isGameOver = entities.getEntitiesWith<SpaceShip>().empty();
        gameState.isWaveOver = entities.getEntitiesWith<Asteroid>().empty();
    }

    glutPostRedisplay();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    entities.createWorld();
}

void reshape (int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    gameState.resizeScreen(w, h);
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
    glutIdleFunc(idle);
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