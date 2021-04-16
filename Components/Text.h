//
// Created by Karl Rombauts on 17/4/21.
//

#ifndef UNTITLED_TEXT_H
#define UNTITLED_TEXT_H

#include <string>
#include "../ecs/Component.h"

struct Text: public Component {
    Text(std::string string): string(string) {}
    std::string string;
};

#endif //UNTITLED_TEXT_H
