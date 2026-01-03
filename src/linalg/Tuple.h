// tuple.h
// Created by Guglielmo Grillo on 30/12/2025.
//
// [TODO] Consider if the w compone is really needed in this implementation.
#pragma once

#include <cmath>
#include <cassert>

#include "macros.h"



/** @brief Tuple class representing a collection of four double values (x, y, z, w).
 * When w=0, it represents a vector in 3D space.
 * When w=1, it represents a point in 3D space.
 *
 * @note The class tries to abstract an affine space using `w` to differentiate between points and vectors.
 * @note All the operations act on all four components, including `w`.
 */
class Tuple {
public:
    double x, y, z, w;

    /** @brief Construct a new Tuple object from the given x, y, z, w values.
     * @param x x-coordinate of the tuple
     * @param y y-coordinate of the tuple
     * @param z z-coordinate of the tuple
     * @param w value indicating if it's a point (1), a vector (0), or a different entity (w != 0 and w != 1)
     * @note No checks are enforced on w.
     */
    Tuple(const double x, const double y, const double z, const double w) : x(x), y(y), z(z), w(w) {}

    /** @brief Create a point Tuple with the given x, y, z coordinates.
     * @param x x-coordinate of the point
     * @param y y-coordinate of the point
     * @param z z-coordinate of the point
     * @return Tuple representing a point (w=1)
     */
    static Tuple point(const double x, const double y, const double z);

    /** @brief Create a vector Tuple with the given x, y, z components.
     * @param x x-component of the vector
     * @param y y-component of the vector
     * @param z z-component of the vector
     * @return Tuple representing a vector (w=0)
     */
    static Tuple vector(const double x, const double y, const double z);


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

    Tuple operator+(const Tuple &other) const {
        double newX = this->x + other.x;
        double newY = this->y + other.y;
        double newZ = this->z + other.z;
        double newW = this->w + other.w;

        return Tuple{newX, newY, newZ, newW};
    }

    Tuple operator-(const Tuple &other) const {
        double newX = this->x - other.x;
        double newY = this->y - other.y;
        double newZ = this->z - other.z;
        double newW = this->w - other.w;

        return Tuple{newX, newY, newZ, newW};
    }

    /** @brief Unary negation operator for Tuple.
     * @return A new Tuple with all components negated.
     * @note The w component is also negated, which may not be standard for 3D points/vectors.
     */
    Tuple operator-() const {
        double newX = -this->x;
        double newY = -this->y;
        double newZ = -this->z;
        double newW = -this->w;

        return Tuple{newX, newY, newZ, newW};
    }

    Tuple& operator+=(const Tuple &other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        this->w += other.w;
        return *this;
    }

    Tuple& operator-=(const Tuple &other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        this->w -= other.w;
        return *this;
    }

    Tuple operator*(const double scalar) const {
        double newX = this->x * scalar;
        double newY = this->y * scalar;
        double newZ = this->z * scalar;
        double newW = this->w * scalar;
        return Tuple{newX, newY, newZ, newW};
    }

    Tuple& operator*=(const double scalar) {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        this->w *= scalar;
        return *this;
    }

    Tuple operator/(const double scalar) const {
        double newX = this->x / scalar;
        double newY = this->y / scalar;
        double newZ = this->z / scalar;
        double newW = this->w / scalar;
        return Tuple{newX, newY, newZ, newW};
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

    /** @brief Compute the dot product between this Tuple and another Tuple.
     * @param other The other Tuple to compute the dot product with.
     * @return The dot product as a double value.
     * @note The dot product is computed using all four components (x, y, z, w).
     */
    double dot(const Tuple &other) const {
        return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
    }

    /** @brief Compute the squared norm (magnitude) of the Tuple.
     * @return The squared norm as a double value.
     * @note The squared norm is computed using all four components (x, y, z, w).
     */
    double norm2() const {
        return this->dot(*this);
    }

    /** @brief Compute the norm (magnitude) of the Tuple.
     * @return The norm as a double value.
     * @note The norm is computed using all four components (x, y, z, w).
     */
    double norm() const {
        return std::sqrt(norm2());
    }

    /** @brief Normalize the Tuple to have a norm of 1.
     * @return A new Tuple that is the normalized version of this Tuple.
     * @note The normalization is done using all four components (x, y, z, w).
     */
    Tuple normalize() const {
        double n = this->norm();
        return Tuple(this->x / n, this->y / n, this->z / n, this->w / n);
    }

    /** @brief Compute the cross product between this Tuple and another Tuple.
     * @param other The other Tuple to compute the cross product with.
     * @return A new Tuple representing the cross product.
     * @note Both Tuples must represent vectors (w=0).
     * @note Unlike other operations, the cross product only involves the x, y, and z components.
     */
    [[nodiscard]]
    Tuple cross(const Tuple &other) const {
        assert(this->is_vector() && other.is_vector());

        double newX = this->y * other.z - this->z * other.y;
        double newY = this->z * other.x - this->x * other.z;
        double newZ = this->x * other.y - this->y * other.x;
        return Tuple::vector(newX, newY, newZ);
    }

};