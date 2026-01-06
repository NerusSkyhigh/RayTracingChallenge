// tuple.h
// Created by Gugli on 30/12/2025.
//

#pragma once

#include <cmath>
#include "assert.h"

#define EPSILON 0.00001
#define APPROX_EQUAL(a, b) (std::fabs((a) - (b)) < EPSILON)

class Color {
public:
    double r, g, b;

    Color(const double r, const double g, const double b) : r(r), g(g), b(b) {}
    Color(): r(0), g(0), b(0) {}

    // Default colors
    static Color Red() { return Color(1.0, 0.0, 0.0); }
    static Color Green() { return Color(0.0, 1.0, 0.0); }
    static Color Blue() { return Color(0.0, 0.0, 1.0); }
    static Color White() { return Color(1.0, 1.0, 1.0); }
    static Color Black() { return Color(0.0, 0.0, 0.0); }

    bool operator==(const Color &other) const {
        bool compatibleX = APPROX_EQUAL(this->r, other.r);
        bool compatibleY = APPROX_EQUAL(this->g, other.g);
        bool compatibleZ = APPROX_EQUAL(this->b, other.b);
        return compatibleX && compatibleY && compatibleZ;
    }

    Color operator+(const Color &other) const {
        return Color(this->r + other.r, this->g + other.g, this->b + other.b);
    }

    Color operator-(const Color &other) const {
        return Color(this->r - other.r, this->g - other.g, this->b - other.b);
    }

    Color operator-() const {
        return Color(-this->r, -this->g, -this->b);
    }

    Color& operator+=(const Color &other) {
        this->r += other.r;
        this->g += other.g;
        this->b += other.b;
        return *this;
    }

    Color& operator-=(const Color &other) {
        this->r -= other.r;
        this->g -= other.g;
        this->b -= other.b;
        return *this;
    }

    Color operator*(const double scalar) const {
        return Color(this->r * scalar, this->g * scalar, this->b * scalar);
    }

    Color& operator*=(const double scalar) {
        this->r *= scalar;
        this->g *= scalar;
        this->b *= scalar;
        return *this;
    }

    Color operator/(const double scalar) const {
        return Color(this->r / scalar, this->g / scalar, this->b / scalar);
    }

    Color& operator/=(const double scalar) {
        this->r /= scalar;
        this->g /= scalar;
        this->b /= scalar;
        return *this;
    }

    Color hadamard(const Color &other) const {
        return Color(this->r * other.r, this->g * other.g, this->b * other.b);
    }


};