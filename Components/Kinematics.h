#ifndef UNTITLED_KINEMATICS_H
#define UNTITLED_KINEMATICS_H


#include "../Vec2.h"

struct Kinematics : public Component {
    Kinematics(const Vec2 &velocity, const Vec2 &acceleration, double mass) : velocity(
            velocity), acceleration(acceleration), mass(mass), angularVelocity(0), drag(0) {}

    Vec2 velocity;
    Vec2 acceleration;
    double angularVelocity;
    double drag;
    double mass;
};


#endif //UNTITLED_KINEMATICS_H
