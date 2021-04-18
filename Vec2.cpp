#include <cmath>
#include "Vec2.h"

Vec2::Vec2(double x, double y): x(x), y(y) {}

Vec2 Vec2::add(Vec2 vector) {
    double newX = this->x + vector.x;
    double newY = this->y + vector.y;
    return Vec2(newX, newY);
}

double Vec2::magnitude() {
    return sqrt(pow(this->x, 2)
              + pow(this->y, 2));
}

Vec2 Vec2::scale(double scalar) {
    double newX = this->x * scalar;
    double newY = this->y * scalar;
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

Vec2 Vec2::operator+(const Vec2 &vector) {
    return this->add(vector);
}

Vec2 Vec2::operator-(Vec2 vector) {

    return this->add(vector.scale(-1));
}

void Vec2::operator+=(const Vec2 &vector) {
    Vec2 newVector = *this + vector;
    this->x = newVector.x;
    this->y = newVector.y;
}

Vec2 Vec2::operator-=(const Vec2 &vector) {
    Vec2 newVector = *this - vector;
    this->x = newVector.x;
    this->y = newVector.y;
}

double Vec2::dot(Vec2 vector) {
    return this->x * vector.x + this->y * vector.y;
}

Vec2 Vec2::normalize() {
    return *this / this->magnitude();
}

Vec2 Vec2::perpendicular() {
    return Vec2(this->y, this->x * -1).normalize();
}

Vec2 Vec2::rotate(double theta) {
    double sinT = sin(theta);
    double cosT = cos(theta);

    return Vec2(this->x * cosT - this->y * sinT, this->x * sinT + this->y * cosT);
}

void Vec2::operator*=(const double &scalar) {
    const Vec2 &newVec = this->scale(scalar);
    this->x = newVec.x;
    this->y = newVec.y;
}

