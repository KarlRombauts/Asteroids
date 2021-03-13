//
// Created by Karl Rombauts on 12/3/21.
//

#ifndef UNTITLED_VEC2_H
#define UNTITLED_VEC2_H

class Vec2 {
public:
    Vec2(double x, double y);
    Vec2 add(Vec2 vector);
    Vec2 scale(double scalar);
    double getMagnitude();
    Vec2 operator+(const Vec2& vector2D);
    Vec2 operator*(const double& scalar);
    Vec2 operator/(const double& scalar);

    double y;
    double x;

    static Vec2 polar(double rotation, double radius);
};

#endif //UNTITLED_VEC2_H
