//
// Created by Karl Rombauts on 19/3/21.
//

#include <iostream>
#include "MouseState.h"
#include "GameModel.h"


MouseState::MouseState()
: leftMouseDown(false), rightMouseDown(false), position({0,0}), drag({0,0}) {}

void MouseState::onMouseDrag(int x, int y) {
    double worldX = ((2 * x / (double) gameModel.width) - 1) * gameModel.worldCoordinates.maxX;
    double worldY = -((2 * y / (double) gameModel.height) - 1) * gameModel.worldCoordinates.maxY;

    drag = Vec2(worldX, worldY);
}

void MouseState::onMouseMove(int x, int y) {

}

void MouseState::onMouseButton(int btn, int state, int x, int y) {
    std::cout << btn << ", " << state << std::endl;
    switch (btn) {
        case 0:
            leftMouseDown = !state;
            break;
        case 2:
            rightMouseDown = !state;
            break;
    }
}

MouseState mouseState;
