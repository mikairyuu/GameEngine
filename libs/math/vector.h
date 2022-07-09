#pragma once

#include <iostream>
#include <math.h>

class Vector2 {


public:
    float x = 0.0f, y = 0.0f;

    Vector2() = default;;

    explicit Vector2(float a) : x(a), y(a) {}

    Vector2(float x, float y) : x(x), y(y) {}

    inline float &operator[](int index) {
        return *(&x + index);
    }

    inline Vector2 &operator=(Vector2 v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    inline Vector2 &operator+=(Vector2 v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    inline Vector2 operator/(float f) const {
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

    inline float operator^(Vector2 &v) const {
        return this->x * v.x + this->y * v.y;
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

    inline Vector2 operator~() const {
        return operator*(-1);
    }

    inline float getLength() {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    inline Vector2 getInvertVector() {
        return this->operator~();
    }
};


class Vector3 {
public:
    float x = 0.0, y = 0.0, z = 0.0;

    Vector3() = default;;

    explicit Vector3(float a) : x(a), y(a), z(a) {}

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    inline float &operator[](int index) {
        return *(&x + index);
    }

    inline Vector3 &operator=(Vector3 v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    inline Vector3 &operator+=(Vector3 v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    inline Vector3 operator/(float f) const {
        return {this->x / f, this->y / f, this->z / f};
    }

    inline Vector3 operator+(Vector3 &v) const {
        return {this->x + v.x, this->y + v.y, this->z + v.z};
    }

    inline Vector3 operator-(Vector3 &v) const {
        return {this->x - v.x, this->y - v.y, this->z - v.z};
    }

    inline Vector3 operator*(Vector3 &v) const {
        return {this->x * v.x, this->y * v.y, this->z * v.z};
    }

    inline float operator^(Vector3 &v) const {
        return this->x * v.x + this->y * v.y + this->z * v.z;
    }

    inline Vector3 operator*(float f) const {
        return {this->x * f, this->y * f, this->z * f};
    }

    inline Vector3 &operator-=(Vector3 v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    inline bool operator==(Vector3 &v) const {
        return this->x == v.x && this->y == v.y && this->z == v.z;
    }

    inline bool operator!=(Vector3 &v) const {
        return !operator==(v);
    }

    inline Vector3 operator~() const {
        return operator*(-1);
    }

    inline float getLength() {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    inline Vector3 getInvertVector() {
        return this->operator~();
    }

};


class Vector4 {
public:
    float x = 0.0, y = 0.0, z = 0.0, q = 0.0;

    Vector4() = default;;

    explicit Vector4(float a) : x(a), y(a), z(a), q(a) {}

    Vector4(float x, float y, float z, float q) : x(x), y(y), z(z), q(q) {}

    inline float &operator[](int index) {
        return *(&x + index);
    }


    inline Vector4 &operator=(Vector4 v) {
        x = v.x;
        y = v.y;
        z = v.z;
        q = v.q;
        return *this;
    }

    inline Vector4 &operator+=(Vector4 v) {
        x += v.x;
        y += v.y;
        z += v.z;
        q += v.q;
        return *this;
    }

    inline Vector4 operator/(float f) const {
        return {this->x / f, this->y / f, this->z / f, this->q / f};
    }

    inline Vector4 operator+(Vector4 &v) const {
        return {this->x + v.x, this->y + v.y, this->z + v.z, this->q + v.q};
    }

    inline Vector4 operator-(Vector4 &v) const {
        return {this->x - v.x, this->y - v.y, this->z - v.z, this->q - v.q};
    }

    inline Vector4 operator*(Vector4 &v)
    {
        return {this->x * v.x, this->y * v.y, this->z * v.z, this->q * v.q};
    }
    inline float operator^(Vector4 &v) const {
        return this->x * v.x + this->y * v.y + this->z * v.z;
    }

    inline Vector4 operator*(float f) const {
        return {this->x * f, this->y * f, this->z * f, this->q * f};
    }

    inline Vector4 &operator-=(Vector4 v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        q -= v.q;
        return *this;
    }

    inline bool operator==(Vector4 &v) const {
        return this->x == v.x && this->y == v.y && this->z == v.z && this->q == v.q;
    }

    inline bool operator!=(Vector4 &v) const {
        return !operator==(v);
    }

    inline Vector4 operator~() const {
        return operator*(-1);
    }

    inline float getLength() {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->q * this->q);
    }

    inline Vector4 getInvertVector() {
        return this->operator~();
    }

};


