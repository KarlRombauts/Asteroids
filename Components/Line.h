//
// Created by Karl Rombauts on 9/4/21.
//

#ifndef UNTITLED_LINE_H
#define UNTITLED_LINE_H


#include "../Vec2.h"
#include "../ecs/Component.h"

struct Line : public Component {
    Line(Vec2 start, Vec2 end): start(start), end(end) {};
    Vec2 start;
    Vec2 end;
};



#endif //UNTITLED_LINE_H
