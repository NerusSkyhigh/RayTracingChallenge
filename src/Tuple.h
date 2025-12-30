// tuple.h
// Created by Gugli on 30/12/2025.
//

#pragma once

#include <cmath>
#include "assert.h"

#define EPSILON 0.00001
#define APPROX_EQUAL(a, b) (std::fabs((a) - (b)) < EPSILON)

class Tuple {
public:
    double x, y, z, w;

    /**
     * @brief Construct a new Tuple object which can be either a point (w=1) or a vector (w=0)
     * @param x
     * @param y
     * @param z
     * @param w
     */
    Tuple(const double x, const double y, const double z, const double w) : x(x), y(y), z(z), w(w) {
        // [TODO] Reintroduce this assert and all the related controls when I have the bigger picture.
        // It should be impossible to create a tuple that is neither a point nor a vector
        // but the book doesn't seem to enforce that strictly.
        //assert(w==0 || w==1);
    }

    static Tuple point(const double x, const double y, const double z) {
        return Tuple(x, y, z, 1.);
    };
    static Tuple vector(const double x, const double y, const double z) {
        return Tuple(x, y, z, 0.);
    };

    bool is_vector() const {
        return APPROX_EQUAL(this->w, 0.);
    }

    bool is_point() const {
        return APPROX_EQUAL(this->w, 1.);
    }

    bool operator==(const Tuple &other) const {
        bool compatibleX = APPROX_EQUAL(this->x, other.x);
        bool compatibleY = APPROX_EQUAL(this->y, other.y);
        bool compatibleZ = APPROX_EQUAL(this->z, other.z);
        bool compatibleW = APPROX_EQUAL(this->w, other.w);
        return compatibleX && compatibleY && compatibleZ && compatibleW;
    }

    // Overload operator +
    Tuple operator+(const Tuple &other) const {
        return Tuple(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
    }

    Tuple operator-(const Tuple &other) const {
        return Tuple(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
    }

    // Overload unary minus
    Tuple operator-() const {
        // [TODO] This should not change w, but the book examples do it this way.
        // At least, there should be a check or something related to w.
        // I will revisit this later.
        // return Tuple(-this->x, -this->y, -this->z, this->w);
        return Tuple(-this->x, -this->y, -this->z, -this->w);
    }

    // Overload +=
    Tuple& operator+=(const Tuple &other) {
        // [TODO] Reintroduce this assert and all the related controls when I have the bigger picture.
        // It should be impossible to create a tuple that is neither a point nor a vector
        // but the book doesn't seem to enforce that strictly.
        //int newW = this->w + other.w;
        //assert(newW == 0 || newW == 1); // Ensure resulting w is valid
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        this->w += other.w;
        return *this;
    }

    Tuple& operator-=(const Tuple &other) {
        // [TODO] Reintroduce this assert and all the related controls when I have the bigger picture.
        // It should be impossible to create a tuple that is neither a point nor a vector
        // but the book doesn't seem to enforce that strictly.
        //int newW = this->w - other.w;
        //assert(newW == 0 || newW == 1); // Ensure resulting w is valid
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        this->w -= other.w;
        return *this;
    }

    // Scalar multiplication and division
    Tuple operator*(const double scalar) const {
        // [TODO] Again, consider whether w should be affected by scalar multiplication.
        return Tuple(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
    }

    Tuple& operator*=(const double scalar) {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        this->w *= scalar;
        return *this;
    }

    Tuple operator/(const double scalar) const {
        return Tuple(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
    }

    Tuple& operator/=(const double scalar) {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
        this->w /= scalar;
        return *this;
    }

    // [TODO] Understand what the books actually wants.
    // The author states we want a 3D vector, but uses 4D tuples everywhere.
    double dot(const Tuple &other) const {
        return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
    }

    double norm2() const {
        return this->dot(*this);
    }

    double norm() const {
        return std::sqrt(norm2());
    }

    Tuple normalize() const {
        double n = this->norm();
        return Tuple(this->x / n, this->y / n, this->z / n, this->w / n);
    }

    // Cross product
    // [TODO] Again, where is w?
    // The author switched back to 3D vectors for this operation
    // without explanations or checks
    Tuple cross(const Tuple &other) const {
        assert(this->is_vector() && other.is_vector());

        return Tuple::vector(
            this->y * other.z - this->z * other.y,
            this->z * other.x - this->x * other.z,
            this->x * other.y - this->y * other.x
        );
    }


};