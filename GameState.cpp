//
// Created by Karl Rombauts on 13/3/21.
//

#include "GameState.h"
#include "OpenGL.h"

GameState gameState;

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
}

CoordinateSpace GameState::getWorldCoordinates() {
    return worldCoordinates;
}

bool GameState::isOutOfBounds(Vec2 vector) {
    return worldCoordinates.isOutOfBounds(vector);
}
