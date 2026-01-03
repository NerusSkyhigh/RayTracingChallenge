//
// Created by Gugli on 30/12/2025.
//

#include "Matrix.h"

Matrix Matrix::translation(const double x, const double y, const double z) {
    Matrix t = Matrix::identity(4);
    t.at(0, 3) = x;
    t.at(1, 3) = y;
    t.at(2, 3) = z;
    // w stays 1
    return t;
}

Matrix Matrix::scaling(const double x, const double y, const double z) {
    Matrix s = Matrix::identity(4);
    s.at(0, 0) = x;
    s.at(1, 1) = y;
    s.at(2, 2) = z;
    // w stays 1
    return s;
}

Matrix Matrix::rotationX(const double radians) {
    // Rotation follows the right-hand rule
    double c = cos(radians);
    double s = sin(radians);

    Matrix r = Matrix::identity(4);

    r.at(1, 1) = c;     r.at(1, 2) = -s;
    r.at(2, 1) = s;     r.at(2, 2) = c;

    return r;
}

Matrix Matrix::rotationY(const double radians) {
    // Rotation follows the right-hand rule
    double c = cos(radians);
    double s = sin(radians);

    Matrix r = Matrix::identity(4);

    r.at(0, 0) = c;     r.at(0, 2) = s;
    r.at(2, 0) = -s;    r.at(2, 2) = c;

    return r;
}

Matrix Matrix::rotationZ(const double radians) {
    // Rotation follows the right-hand rule
    double c = cos(radians);
    double s = sin(radians);

    Matrix r = Matrix::identity(4);

    r.at(0, 0) = c;     r.at(0, 1) = -s;
    r.at(1, 0) = s;     r.at(1, 1) = c;

    return r;
}

Matrix Matrix::shearing(const double xy, const double xz,
                       const double yx, const double yz,
                       const double zx, const double zy) {
    std::vector<double> data = {
        1, xy, xz, 0,
        yx, 1, yz, 0,
        zx, zy, 1, 0,
        0, 0, 0, 1
    };

    return Matrix(4, data);
}