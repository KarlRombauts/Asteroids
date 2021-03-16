//
// Created by Karl Rombauts on 16/3/21.
//

#ifndef UNTITLED_GRAVITYFORCE_H
#define UNTITLED_GRAVITYFORCE_H


struct GravityForce : public Component {
    GravityForce(double mass) : mass(mass) {}

    double mass;
};


#endif //UNTITLED_GRAVITYFORCE_H
