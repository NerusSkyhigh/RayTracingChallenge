//
// Created by Gugli on 03/01/2026.
//

#pragma once
#include "linalg/Tuple.h"

#include "renderer/Ray.h"

#include "Intersections.h"
#include "Shape.h"


/**@brief Represents a hit intersection
 *
 */
class Hit {
public:
    double t;
    Tuple point;
    const Shape* shape;

private:
    Hit() : t(std::numeric_limits<double>::infinity()), point(Tuple::point(0,0,0)) {};
    Hit(const Shape& shape): t(std::numeric_limits<double>::infinity()), shape(&shape), point(Tuple::point(0,0,0)) {};
    Hit(const double t, const Shape& shape, Tuple point) : t(t), shape(&shape), point(point) {}

public:
    static Hit find(const Intersections& intersections, const Ray ray);

    bool isValid() const {
        return t != std::numeric_limits<double>::infinity();
    }
};
