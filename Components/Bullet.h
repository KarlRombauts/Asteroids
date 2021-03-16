//
// Created by Karl Rombauts on 15/3/21.
//

#ifndef UNTITLED_BULLET_H
#define UNTITLED_BULLET_H


struct Bullet : public Component {
    Bullet(int damage) : damage(damage) {}

    int damage;
};


#endif //UNTITLED_BULLET_H
