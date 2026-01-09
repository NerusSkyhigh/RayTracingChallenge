//
// Created by Gugli on 02/01/2026.
//
#pragma once

#include "linalg/Tuple.h"
#include "linalg/Matrix.h"



class Ray {
public:
    Tuple origin;
    Tuple direction; /// Versor indicating the ray's direction; normalization is NOT enforced to allow for rays to encode information about scaling

    Ray(Tuple direction) : origin(Tuple::point(0, 0, 0)), direction(direction) {}

    Ray(Tuple origin, Tuple direction) : origin(origin), direction(direction) {}

    Ray(double x0, double y0, double z0, double dx, double dy, double dz)
        : origin(Tuple::point(x0, y0, z0)), direction(Tuple::vector(dx, dy, dz)) {}


    /**
     * In the book this is called position(t)
     * @param t
     * @return
     */
    Tuple cast(double t) const {
        return origin + direction * t;
    }

    Ray transform(const Matrix& m) const {
        Tuple newOrigin = m * origin;
        Tuple newDirection = m * direction;
        return Ray(newOrigin, newDirection);
    }


};