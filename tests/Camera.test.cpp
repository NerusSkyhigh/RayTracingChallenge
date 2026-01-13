#define _USE_MATH_DEFINES
#include <cmath>

#include <catch2/catch_test_macros.hpp>


#include "linalg/macros.h"
#include "render/Camera.h"

TEST_CASE("Creating a camera") {
    int hsize = 160;
    int vsize = 120;
    double fieldOfView = M_PI / 2.0;

    Camera c(hsize, vsize, fieldOfView);

    REQUIRE(c.hsize == 160);
    REQUIRE(c.vsize == 120);
    REQUIRE( APPROX_EQUAL(c.fieldOfView, M_PI / 2.0));
    REQUIRE(c.GetTransform() == Matrix::identity(4));
}

TEST_CASE("The pixel size for a horizontal canvas") {
    Camera c(200, 125, M_PI / 2.0);

    REQUIRE( APPROX_EQUAL(c.pixelSize, 0.01));
}

TEST_CASE("Constructing a ray through the center of the canvas") {
    Camera c(201, 101, M_PI / 2.0);
    Ray r = c.rayForPixel(100, 50);

    REQUIRE(r.origin == Tuple::point(0, 0, 0));
    REQUIRE(r.direction == Tuple::vector(0, 0, -1));
}

TEST_CASE("Constructing a ray through a corner of the canvas") {
    Camera c(201, 101, M_PI / 2.0);
    Ray r = c.rayForPixel(0, 0);

    REQUIRE(r.origin == Tuple::point(0, 0, 0));
    REQUIRE(r.direction == Tuple::vector(0.66519, 0.33259, -0.66851));
}

TEST_CASE("Constructing a ray when the camera is transformed") {
    Camera c(201, 101, M_PI / 2.0);
    c.SetTransform(
        Matrix::rotationY(M_PI / 4.0) *
        Matrix::translation(0, -2, 5)
    );
    Ray r = c.rayForPixel(100, 50);

    REQUIRE(r.origin == Tuple::point(0, 2, -5));
    REQUIRE(r.direction == Tuple::vector(sqrt(2)/2, 0, -sqrt(2)/2));
}