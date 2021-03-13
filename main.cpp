#include <stdlib.h>
#include <stdio.h>

#if _WIN32
    # include <windows.h>
#endif

#if __APPLE__
    # include <OpenGL/gl.h>
    # include <OpenGL/glu.h>
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

/* Display callback */
static float rotDeg = 0.0f;
static float lastTime = 0;

Ship ship(Vec2(0.5, 0.5), 0.0, 5.0, 1);
EntityManager entities;
RenderSystem renderSystem;
PhysicsSystem physicsSystem;
PlayerInputSystem playerInputSystem;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    renderSystem.update(entities, 0);
    glutSwapBuffers();
}

/* Keyboard callback */
void onKeyPress(unsigned char key, int x, int y) {
    keyboardState.setPressedKey(key);
    switch (key) {
        case 27:
        case 'q':
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
  }
}

void onKeyRelease(unsigned char key, int x, int y) {
    keyboardState.releaseKey(key);
}

static void idle_func(void)
{
    int thisTime;

    thisTime = glutGet(GLUT_ELAPSED_TIME);
    float dt = thisTime - lastTime;

    rotDeg += (float)dt * 0.1f;

//    ship.update(dt);

    playerInputSystem.update(entities, dt);
    physicsSystem.update(entities, dt);

    lastTime = thisTime;

    glutPostRedisplay();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    GLdouble aspectRatio = (GLfloat) h / (GLfloat) w;
    if (w <= h)
        gameState.resizeWorld(-2, 2, -2, 2 * aspectRatio);
    else
        gameState.resizeWorld(-2, 2 / aspectRatio, -2, 2);
}

void init() {
    /* In this simple program these OpenGL calls only need to be done once, */
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    Entity *spaceShip = entities.create();
    spaceShip->assign<Transform>(1, 1,  10, OutOfBoundsBehaviour::WRAP);
    spaceShip->assign<Moveable>(Vec2(0.1, 0.2), Vec2(0, 0));
    spaceShip->assign<PlayerInput>();

    Entity *asteroid = entities.create();
    asteroid->assign<Transform>(0, 0, 0, OutOfBoundsBehaviour::BOUNCE);
    asteroid->assign<Moveable>(Vec2(0.3, 0.2), Vec2(0, 0));

    Entity *asteroid2 = entities.create();
    asteroid2->assign<Transform>(-0.7, 0.3, 0, OutOfBoundsBehaviour::BOUNCE);
    asteroid2->assign<Moveable>(Vec2(-0.4, 0.5), Vec2(0, 0));
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Asteroids");
    init();

    /* Display and keyboard callbacks */
    glutIdleFunc(idle_func);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(onKeyPress);
    glutKeyboardUpFunc(onKeyRelease);
    /* Let glut take over */
    glutMainLoop();

//    std::vector<Entity *> entitiesWithMomentum = entities.getEntitiesWith<Momentum, Rotation, PlayerInput>();
}