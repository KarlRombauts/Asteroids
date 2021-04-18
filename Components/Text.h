//
// Created by Karl Rombauts on 17/4/21.
//

#ifndef UNTITLED_TEXT_H
#define UNTITLED_TEXT_H

#include <string>
#include "../ecs/Component.h"

struct Text: public Component {
    Text(std::string string, TextAlignment alignment): string(string), alignment(alignment) {}
    std::string string;
    TextAlignment alignment;
};

#endif //UNTITLED_TEXT_H
