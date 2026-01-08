#include "catch2/catch_test_macros.hpp"

#include "renderer/Ray.h"
#include "shapes/Sphere.h"
#include "shapes/Intersections.h"

TEST_CASE("The hit, when all intersections have positive t") {
    Sphere sphere;
    Intersections xs;

    // Dummy tuples for intersection data
    Tuple dummyTuple = Tuple::point(0,0,0);

    xs.add(sphere, 1.0, dummyTuple, dummyTuple, dummyTuple);
    xs.add(sphere, 2.0, dummyTuple, dummyTuple, dummyTuple);

    xs.sort();

    Hit hit = xs.GetHit();
    REQUIRE(hit.valid);
    REQUIRE(APPROX_EQUAL(hit.t, 1.0));
}


TEST_CASE("The hit, when some intersections have negative t") {
    Sphere sphere;
    Intersections intersections;

    // Dummy tuples for intersection data
    Tuple dummyTuple = Tuple::point(0,0,0);
    intersections.add(sphere, -1.0, dummyTuple, dummyTuple, dummyTuple);
    intersections.add(sphere,  1.0, dummyTuple, dummyTuple, dummyTuple);

    Hit hit = intersections.GetHit();

    REQUIRE(hit.valid);
    REQUIRE(APPROX_EQUAL(hit.t, 1.0));
}

TEST_CASE("The hit, when all intersections have negative t") {
    Sphere sphere;
    Intersections intersections;

    // Dummy tuples for intersection data
    Tuple dummyTuple = Tuple::point(0,0,0);
    intersections.add(sphere, -2.0, dummyTuple, dummyTuple, dummyTuple);
    intersections.add(sphere, -1.0, dummyTuple, dummyTuple, dummyTuple);

    Hit hit = intersections.GetHit();

    REQUIRE(!hit.valid );
}



TEST_CASE("The hit is the lowest non-negative intersection") {
    Sphere sphere;
    Intersections intersections;

    // Dummy tuples for intersection data
    Tuple dummyTuple = Tuple::point(0,0,0);
    intersections.add(sphere, 5.0, dummyTuple, dummyTuple, dummyTuple);
    intersections.add(sphere, 7.0, dummyTuple, dummyTuple, dummyTuple);
    intersections.add(sphere, -3.0, dummyTuple, dummyTuple, dummyTuple);
    intersections.add(sphere, 2.0, dummyTuple, dummyTuple, dummyTuple);

    Hit hit = intersections.GetHit();


    REQUIRE(hit.valid);
    REQUIRE(APPROX_EQUAL(hit.t, 2.0));
}