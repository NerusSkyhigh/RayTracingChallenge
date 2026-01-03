#include "catch2/catch_test_macros.hpp"

#include "renderer/Ray.h"
#include "shapes/Sphere.h"
#include "shapes/Intersections.h"


TEST_CASE("A ray intersects a sphere at two points") {
    Ray ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere sphere(1.0);

    Intersections intersection = ray.intersect(sphere);

    REQUIRE(intersection.size == 2);
    REQUIRE(APPROX_EQUAL(intersection.solutions[0], 4.0));
    REQUIRE(APPROX_EQUAL(intersection.solutions[1], 6.0));
}

TEST_CASE("A ray intersects a sphere at a tangent") {
    Ray ray(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1));
    Sphere sphere(1.0);

    Intersections intersection = ray.intersect(sphere);

    REQUIRE(intersection.size == 2);
    REQUIRE(APPROX_EQUAL(intersection.solutions[0], 5.0));
    REQUIRE(APPROX_EQUAL(intersection.solutions[1], 5.0));
}

TEST_CASE("A ray misses a sphere") {
    Ray ray(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1));
    Sphere sphere(1.0);

    Intersections intersection = ray.intersect(sphere);

    REQUIRE(intersection.size == 0);
}

TEST_CASE("A ray originates inside a sphere") {
    Ray ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Sphere sphere(1.0);

    Intersections intersection = ray.intersect(sphere);

    REQUIRE(intersection.size == 2);
    REQUIRE(APPROX_EQUAL(intersection.solutions[0], -1.0));
    REQUIRE(APPROX_EQUAL(intersection.solutions[1], 1.0));
}

TEST_CASE("A sphere is behind a ray") {
    Ray ray(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
    Sphere sphere(1.0);

    Intersections intersection = ray.intersect(sphere);

    REQUIRE(intersection.size == 2);
    REQUIRE(APPROX_EQUAL(intersection.solutions[0], -6.0));
    REQUIRE(APPROX_EQUAL(intersection.solutions[1], -4.0));
}

TEST_CASE("An intersection encapsulates t and object") {
    Sphere sphere(1.0);
    Intersections intersection(sphere);
    intersection.addSolution(3.5);

    REQUIRE(APPROX_EQUAL(intersection.solutions[0], 3.5));
    REQUIRE(intersection.shape == &sphere);
}