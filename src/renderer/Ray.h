//
// Created by Gugli on 02/01/2026.
//
#pragma once

#include "linalg/Tuple.h"
#include "linalg/Matrix.h"
#include "shapes/Sphere.h"
#include "shapes/Intersections.h"



class Ray {
public:
    Tuple origin;
    Tuple direction;

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

    /**
     * @brief Detects intersections of the ray with a sphere of radius 1 centered at the origin
     * @param sphere
     * @return
     */
    Intersections intersect(const Sphere& sphere) const;


    Ray transform(const Matrix& m) const {
        Tuple newOrigin = m * origin;
        Tuple newDirection = m * direction;
        return Ray(newOrigin, newDirection);
    }


};