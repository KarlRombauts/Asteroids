//
// Created by Karl Rombauts on 13/3/21.
//

#ifndef UNTITLED_GAMESTATE_H
#define UNTITLED_GAMESTATE_H


#include "Coordinates.h"

class GameState {
private:
    CoordinateSpace worldCoordinates;

public:
    void resizeWorld(double aspectRatio);

    void resizeWorld(double minX, double maxX, double minY, double maxY);

    CoordinateSpace getWorldCoordinates();

    bool isOutOfBounds(Vec2 vector);
};

extern GameState gameState;

#endif //UNTITLED_GAMESTATE_H
