//
// Created by Karl Rombauts on 13/3/21.
//

#ifndef UNTITLED_GAMESTATE_H
#define UNTITLED_GAMESTATE_H


#include "Coordinates.h"

struct GameState {
    int worldSize = 100;
    int width;
    int height;

    CoordinateSpace worldCoordinates;

    void resizeWorld(double aspectRatio);

    void resizeScreen(int w, int h);

    void resizeWorld(double minX, double maxX, double minY, double maxY);

    bool isOutOfBounds(Vec2 vector);

    CoordinateSpace getWorldCoordinates();
};

extern GameState gameState;

#endif //UNTITLED_GAMESTATE_H
