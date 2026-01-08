// ViewTransform.h
// Created by Gugli on 07/01/2026.
//
#pragma once

#include <vector>

#include "Tuple.h"
#include "Matrix.h"

class ViewTransform {
private:
    Matrix transform;
    Matrix itransform;

public:
    Tuple up;
    Tuple forward;
    Tuple right;

    ViewTransform() : up(Tuple::vector(0, 1, 0)),
                      forward(Tuple::vector(0, 0, -1)),
                      right(Tuple::vector(1, 0, 0)),
                      transform(Matrix::identity(4)),
                      itransform(Matrix::identity(4)) {}

    ViewTransform(const Tuple& from, const Tuple& to, const Tuple& upVector) {

        this->forward = (to - from).normalize();
        this->right = this->forward.cross(upVector).normalize();
        this->up = this->right.cross(this->forward).normalize();

        std::vector<double> orientationData = {
             this->right.x,    this->right.y,    this->right.z,     0,
             this->up.x,       this->up.y,       this->up.z,        0,
            -this->forward.x, -this->forward.y, -this->forward.z,   0,
            0,                 0,                0,                 1
        };
        this->transform = Matrix(4, orientationData);

        Matrix translation = Matrix::translation(-from.x, -from.y, -from.z);
        this->transform = this->transform * translation;
        this->itransform = transform.inverse();

    }

    Matrix GetTransform() const {
        return transform;
    }

    Matrix GetInverseTransform() const {
        return itransform;
    }
};