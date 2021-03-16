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
    Vec2 operator+(const Vec2& vector);
    void operator+=(const Vec2& vector);
    Vec2 operator-(const Vec2& vector);
    Vec2 operator-=(const Vec2& vector);
    Vec2 operator*(const double& scalar);
    Vec2 operator/(const double& scalar);

    double y;
    double x;

    static Vec2 polar(double rotation, double radius);

    static double distanceBetween(Vec2 v1, Vec2 v2);

};

#endif //UNTITLED_VEC2_H
