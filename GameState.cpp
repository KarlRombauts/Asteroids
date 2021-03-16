//
// Created by Karl Rombauts on 13/3/21.
//

#include "GameState.h"
#include "OpenGL.h"

GameState gameState;

void GameState::resizeWorld(double aspectRatio) {
    int size = 100;

    if (aspectRatio > 1)
        gameState.resizeWorld(-size, size, -size * aspectRatio, size * aspectRatio);
    else
        gameState.resizeWorld(-size / aspectRatio, size / aspectRatio, -size, size);
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
