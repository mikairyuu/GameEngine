#pragma once
#include <iostream>

class Vector2 {


public:
    float x = 0.0, y = 0.0;

    Vector2(){};

    explicit Vector2(float a) : x(a), y(a) {}

    Vector2(float x, float y) : x(x), y(y) {}

    inline float &operator[](int index) {
        return *(&x + index);
    }

    inline const float &operator[](int index) const {
        return *(&x + index);
    }

    inline Vector2 &operator=(Vector2 right) {
        x = right.x;
        y = right.y;
        return *this;
    }

    inline Vector2 &operator+=(Vector2 right) {
        x += right.x;
        y += right.y;
        return *this;
    }
    inline Vector2 operator/(float f) const
    {
        return {this->x / f, this->y / f};
    }

    inline Vector2 operator+(Vector2 &v) const {
        return {this->x + v.x, this->y + v.y};
    }

    inline Vector2 operator-(Vector2 &v) const {
        return {this->x - v.x, this->y - v.y};
    }

    inline Vector2 operator*(Vector2 &v) const {
        return {this->x * v.x, this->y * v.y};
    }

    inline Vector2 operator*(float f) const {
        return {this->x * f, this->y * f};
    }

    inline Vector2 &operator-=(Vector2 v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    inline bool operator==(Vector2 &v) const {
        return this->x == v.x && this->y == v.y;
    }

    inline bool operator!=(Vector2 &v) const {
        return !operator==(v);
    }
};