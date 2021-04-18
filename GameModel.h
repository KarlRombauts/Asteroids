#ifndef UNTITLED_GAMEMODEL_H
#define UNTITLED_GAMEMODEL_H

#include "Coordinates.h"

enum class GameState {
    GAME_OVER,
    WAVE_OVER,
    PLAYING,
    START,
    PLAY_AGAIN,
};

struct GameModel {
    int worldSize = 100;
    int arenaSize = worldSize - 10;
    int waveCount = 1;
    int msElapsedTime = 0;
    int score = 0;
    GameState state = GameState::START;

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

extern GameModel gameModel;

#endif //UNTITLED_GAMEMODEL_H
