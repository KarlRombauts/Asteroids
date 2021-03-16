//
// Created by Karl Rombauts on 14/3/21.
//

#ifndef UNTITLED_TEXTURE_H
#define UNTITLED_TEXTURE_H

#include "../ecs/Component.h"

struct Texture: public Component {
    Texture(float red, float green, float blue)
        : red(red), green(green), blue(blue) {}

    float red;
    float green;
    float blue;
};

#endif //UNTITLED_TEXTURE_H
