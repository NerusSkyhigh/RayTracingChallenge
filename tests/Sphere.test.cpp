#include "../src/renderer/Ray.h"
#include "catch2/catch_test_macros.hpp"

#include "../src/shapes/Sphere.h"

TEST_CASE("A sphere default transform") {
    Sphere s(1.0);
    Matrix identity = Matrix::identity(4);
    REQUIRE(s.transform == identity);
}

TEST_CASE("Changing a sphere's transform") {
    Sphere s(1.0);
    Matrix translation = Matrix::translation(2, 3, 4);
    s.setTransform(translation);
    REQUIRE(s.transform == translation);
}

TEST_CASE("Intersecting a scaled sphere with a ray") {
    Tuple rayOrigin = Tuple::point(0, 0, -5);
    Tuple rayDirection = Tuple::vector(0, 0, 1);
    Ray ray(rayOrigin, rayDirection);

    Sphere sphere(1.0);
    sphere.setTransform(Matrix::scaling(2, 2, 2));

    Intersections intersection = ray.transform( sphere.transform.inverse()).intersect(sphere);

    REQUIRE(intersection.size == 2);
    REQUIRE(APPROX_EQUAL(intersection.solutions[0], 3.0));
    REQUIRE(APPROX_EQUAL(intersection.solutions[1], 7.0));
}

TEST_CASE("Intersecting a translated sphere with a ray") {
    Tuple rayOrigin = Tuple::point(0, 0, -5);
    Tuple rayDirection = Tuple::vector(0, 0, 1);
    Ray ray(rayOrigin, rayDirection);

    Sphere sphere(1.0);
    sphere.setTransform(Matrix::translation(5, 0, 0));

    Intersections intersection = ray.transform( sphere.transform.inverse()).intersect(sphere);

    REQUIRE(intersection.size == 0);
}