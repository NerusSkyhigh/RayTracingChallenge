#include "catch2/catch_test_macros.hpp"

#include "shapes/Sphere.h"
#include "shapes/Intersections.h"
#include "shapes/Hit.h"

TEST_CASE("The hit, when all intersections have positive t") {
    Sphere sphere(1.0);
    Intersections intersections(sphere);
    intersections.addSolution(1.0);
    intersections.addSolution(2.0);

    // Dummy ray for Hit::find
    Tuple origin = Tuple::point(0,0, 0);
    Tuple direction = Tuple::vector(0,0,1);
    Ray ray(origin, direction);

    Hit hit = Hit::find(intersections, ray);

    REQUIRE(hit.isValid() );
    REQUIRE(APPROX_EQUAL(hit.t, 1.0));
}


TEST_CASE("The hit, when some intersections have negative t") {
    Sphere sphere(1.0);
    Intersections intersections(sphere);
    intersections.addSolution(-1.0);
    intersections.addSolution(1.0);

    // Dummy ray for Hit::find
    Tuple origin = Tuple::point(0,0, 0);
    Tuple direction = Tuple::vector(0,0,1);
    Ray ray(origin, direction);

    Hit hit = Hit::find(intersections, ray);
    REQUIRE(hit.isValid() );
    REQUIRE(APPROX_EQUAL(hit.t, 1.0));
}

TEST_CASE("The hit, when all intersections have negative t") {
    Sphere sphere(1.0);
    Intersections intersections(sphere);
    intersections.addSolution(-2.0);
    intersections.addSolution(-1.0);

    // Dummy ray for Hit::find
    Tuple origin = Tuple::point(0,0, 0);
    Tuple direction = Tuple::vector(0,0,1);
    Ray ray(origin, direction);

    Hit hit = Hit::find(intersections, ray);

    REQUIRE(!hit.isValid() );
}



TEST_CASE("The hit is the lowest non-negative intersection") {
    Sphere sphere(1.0);
    Intersections intersections(sphere);
    intersections.addSolution(5.0);
    intersections.addSolution(7.0);
    intersections.addSolution(-3.0);
    intersections.addSolution(2.0);

    // Dummy ray for Hit::find
    Tuple origin = Tuple::point(0,0, 0);
    Tuple direction = Tuple::vector(0,0,1);
    Ray ray(origin, direction);

    Hit hit = Hit::find(intersections, ray);

    REQUIRE(hit.isValid() );
    REQUIRE(APPROX_EQUAL(hit.t, 2.0));
}