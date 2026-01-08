#include <catch2/catch_test_macros.hpp>

#include "linalg/ViewTransform.h"
#include "linalg/Tuple.h"
#include "linalg/Matrix.h"

TEST_CASE("The transformation matrix for the default orientation") {
    Tuple from = Tuple::point(0, 0, 0);
    Tuple to = Tuple::point(0, 0, -1);
    Tuple up = Tuple::vector(0, 1, 0);

    ViewTransform vt(from, to, up);
    Matrix t = vt.GetTransform();

    REQUIRE(t == Matrix::identity(4));
}

TEST_CASE("A view transformation matrix looking in positive z direction") {
    Tuple from = Tuple::point(0, 0, 0);
    Tuple to = Tuple::point(0, 0, 1);
    Tuple up = Tuple::vector(0, 1, 0);

    ViewTransform vt(from, to, up);
    Matrix t = vt.GetTransform();

    REQUIRE(t == Matrix::scaling(-1, 1, -1));
}

TEST_CASE("The view transformation moves the world") {
    Tuple from = Tuple::point(0, 0, 8);
    Tuple to = Tuple::point(0, 0, 0);
    Tuple up = Tuple::vector(0, 1, 0);

    ViewTransform vt(from, to, up);
    Matrix transform = vt.GetTransform();
    Matrix expected = Matrix::translation(0, 0, -8);

    REQUIRE(transform == expected);
}