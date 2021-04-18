//
// Created by Karl Rombauts on 12/3/21.
//

#ifndef UNTITLED_VEC2_H
#define UNTITLED_VEC2_H

class Vec2 {
public:
    Vec2(double x, double y);
    Vec2 add(Vec2 vector);
    double dot(Vec2 vector);
    Vec2 scale(double scalar);
    Vec2 normalize();
    double magnitude();

    Vec2 operator+(const Vec2& vector);
    void operator+=(const Vec2& vector);
    Vec2 operator-(Vec2 vector);
    Vec2 operator-=(const Vec2& vector);
    void operator*=(const double& scalar);
    Vec2 operator*(const double& scalar);
    Vec2 operator/(const double& scalar);

    double y;
    double x;

    static Vec2 polar(double rotation, double radius);

    Vec2 perpendicular();

    Vec2 rotate(double theta);
};

#endif //UNTITLED_VEC2_H
