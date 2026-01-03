#include "catch2/catch_test_macros.hpp"

#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"


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

TEST_CASE("The hit, when all intersections have positive t") {
    Sphere sphere(1.0);
    Intersections intersections(sphere);
    intersections.addSolution(1.0);
    intersections.addSolution(2.0);

    Intersections hit = Intersections::hit(intersections);

    REQUIRE(hit.size == 1);
    REQUIRE(APPROX_EQUAL(hit.solutions[0], 1.0));
}

TEST_CASE("The hit, when some intersections have negative t") {
    Sphere sphere(1.0);
    Intersections intersections(sphere);
    intersections.addSolution(-1.0);
    intersections.addSolution(1.0);

    Intersections hit = Intersections::hit(intersections);

    REQUIRE(hit.size == 1);
    REQUIRE(APPROX_EQUAL(hit.solutions[0], 1.0));
}

TEST_CASE("The hit, when all intersections have negative t") {
    Sphere sphere(1.0);
    Intersections intersections(sphere);
    intersections.addSolution(-2.0);
    intersections.addSolution(-1.0);

    Intersections hit = Intersections::hit(intersections);

    REQUIRE(hit.size == 0);
}

TEST_CASE("The hit is the lowest non-negative intersection") {
    Sphere sphere(1.0);
    Intersections intersections(sphere);
    intersections.addSolution(5.0);
    intersections.addSolution(7.0);
    intersections.addSolution(-3.0);
    intersections.addSolution(2.0);

    Intersections hit = Intersections::hit(intersections);

    REQUIRE(hit.size == 1);
    REQUIRE(APPROX_EQUAL(hit.solutions[0], 2.0));
}
