//
// Created by Karl Rombauts on 12/3/21.
//

#include <cmath>
#include "Vec2.h"

Vec2::Vec2(double x, double y): x(x), y(y) {}

Vec2 Vec2::add(Vec2 vector) {
    double newX = this->x + vector.x;
    double newY = this->y + vector.y;
    return Vec2(newX, newY);
}

double Vec2::getMagnitude() {
    return sqrt(pow(this->x, 2)
              + pow(this->y, 2));
}

Vec2 Vec2::scale(double scalar) {
    double newX = this->x / scalar;
    double newY = this->y / scalar;
    return Vec2(newX, newY);
}

Vec2 Vec2::operator*(const double &scalar) {
    return this->scale(scalar);
}

Vec2 Vec2::operator/(const double &scalar) {
    return this->scale(1/scalar);
}

Vec2 Vec2::polar(double rotation, double radius) {
    double x = cos(rotation * (M_PI / 180)) * radius;
    double y = sin(rotation * (M_PI / 180)) * radius;
    return Vec2(x, y);
}

Vec2 Vec2::operator+(const Vec2 &vector2D) {
    return this->add(vector2D);
}
