#ifndef UNTITLED_GAMESTATE_H
#define UNTITLED_GAMESTATE_H

#include "Coordinates.h"

struct GameState {
    int worldSize = 100;
    int arenaSize = worldSize - 10;
    int waveCount = 1;
    int msElapsedTime = 0;
    int score = 0;
    bool isGameOver = false;
    bool isWaveOver = true;

    int width;
    int height;
    CoordinateSpace worldCoordinates;

    void resizeWorld(double aspectRatio);

    void resizeScreen(int w, int h);

    void resizeWorld(double minX, double maxX, double minY, double maxY);

    CoordinateSpace getWorldCoordinates();

    bool isCircleInArena(Vec2 pos, double radius);

    double getWorldToPixelRatioWidth();

    void reset();

};

extern GameState gameState;

#endif //UNTITLED_GAMESTATE_H
