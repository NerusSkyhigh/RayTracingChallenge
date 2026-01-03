#include "../src/renderer/Ray.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Creating and querying a ray") {
    Tuple origin = Tuple::point(1, 2, 3);
    Tuple direction = Tuple::vector(4, 5, 6);
    Ray ray(origin, direction);

    REQUIRE(ray.origin == origin);
    REQUIRE(ray.direction == direction);
}

TEST_CASE("Computing point from a distance") {
    Tuple origin = Tuple::point(2, 3, 4);
    Tuple direction = Tuple::vector(1, 0, 0);
    Ray ray(origin, direction);

    REQUIRE(ray.cast(0) == Tuple::point(2, 3, 4));
    REQUIRE(ray.cast(1) == Tuple::point(3, 3, 4));
    REQUIRE(ray.cast(-1) == Tuple::point(1, 3, 4));
    REQUIRE(ray.cast(2.5) == Tuple::point(4.5, 3, 4));
}

TEST_CASE("Translating a ray") {
    Ray ray(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));
    Matrix translation = Matrix::translation(3, 4, 5);
    Ray movedRay = ray.transform(translation);

    REQUIRE(movedRay.origin == Tuple::point(4, 6, 8));
    REQUIRE(movedRay.direction == Tuple::vector(0, 1, 0));
}

TEST_CASE("Scaling a ray") {
    Ray ray(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));
    Matrix scaling = Matrix::scaling(2, 3, 4);
    Ray scaledRay = ray.transform(scaling);

    REQUIRE(scaledRay.origin == Tuple::point(2, 6, 12));
    REQUIRE(scaledRay.direction == Tuple::vector(0, 3, 0));
}