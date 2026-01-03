//
// Created by Gugli on 03/01/2026.
//
#pragma once
#include "Tuple.h"
#include "Shape.h"
#include "Matrix.h"

class Sphere : public Shape {
public:
    double radius; // [TODO] Set this to 1
    Tuple origin; // [TODO] Set this to (0,0,0)
    Matrix transform;

    Sphere(): radius(1.0), origin(Tuple::point(0,0,0)), transform(Matrix::identity(4)) {}

    Sphere(double r) : radius(r), origin(Tuple::point(0,0,0)), transform(Matrix::identity(4)) {}
    Sphere(const double r, const Tuple origin) : radius(r), origin(origin), transform(Matrix::identity(4)) {}

    const bool operator==(const Sphere&) const {
        bool sameRadius = APPROX_EQUAL(this->radius, radius);
        bool sameOrigin = this->origin == origin;
        return sameRadius && sameOrigin;
    }

    void setTransform(const Matrix& m) {
        this->transform = m;
    }

    void addTransform(const Matrix& m) {
        this->transform = m * this->transform;
    }

    void resetTransform() {
        this->transform = Matrix::identity(4);
    }


};
