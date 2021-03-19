//
// Created by Karl Rombauts on 13/3/21.
//

#include "GameState.h"
#include "OpenGL.h"

GameState gameState;

void GameState::resizeWorld(double aspectRatio) {


    if (aspectRatio > 1)
        gameState.resizeWorld(-worldSize, worldSize, -worldSize * aspectRatio, worldSize * aspectRatio);
    else
        gameState.resizeWorld(-worldSize / aspectRatio, worldSize / aspectRatio, -worldSize, worldSize);
}
void GameState::resizeWorld(double minX, double maxX, double minY, double maxY) {
    worldCoordinates.minX = minX;
    worldCoordinates.maxX = maxX;
    worldCoordinates.minY = minY;
    worldCoordinates.maxY = maxY;

    glMatrixMode (GL_PROJECTION);
        glLoadIdentity();
        glOrtho(minX, maxX, minY, maxY, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    glutPostRedisplay();
}

CoordinateSpace GameState::getWorldCoordinates() {
    return worldCoordinates;
}

bool GameState::isOutOfBounds(Vec2 vector) {
    return worldCoordinates.isOutOfBounds(vector);
}

void GameState::resizeScreen(int w, int h) {
    width = w;
    height = h;
    GLdouble aspectRatio = (GLfloat) h / (GLfloat) w;
    gameState.resizeWorld(aspectRatio);
}
