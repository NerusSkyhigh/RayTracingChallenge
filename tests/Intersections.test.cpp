#include "catch2/catch_test_macros.hpp"

#include "renderer/Ray.h"
#include "shapes/Sphere.h"
#include "shapes/Intersections.h"


TEST_CASE("A ray intersects a sphere at two points") {
    Ray ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere sphere;

    Intersections xs;
    sphere.intersect(ray, xs);

    REQUIRE(xs.size == 2);
    REQUIRE(APPROX_EQUAL(xs[0].t, 4.0));
    REQUIRE(APPROX_EQUAL(xs[1].t, 6.0));
}

TEST_CASE("A ray intersects a sphere at a tangent") {
    Ray ray(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1));
    Sphere sphere;

    Intersections xs;
    sphere.intersect(ray, xs);

    REQUIRE(xs.size == 2);
    REQUIRE( APPROX_EQUAL(xs[0].t, 5.0) );
    REQUIRE( APPROX_EQUAL(xs[1].t, 5.0) );
}

TEST_CASE("A ray misses a sphere") {
    Ray ray(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1));
    Sphere sphere;

    Intersections xs;
    sphere.intersect(ray, xs);

    REQUIRE(xs.size == 0);
}

TEST_CASE("A ray originates inside a sphere") {
    Ray ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Sphere sphere;

    Intersections xs;
    sphere.intersect(ray, xs);

    REQUIRE(xs.size == 2);
    REQUIRE(APPROX_EQUAL(xs[0].t, -1.0));
    REQUIRE(APPROX_EQUAL(xs[1].t, 1.0));
}

TEST_CASE("A sphere is behind a ray") {
    Ray ray(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
    Sphere sphere;

    Intersections xs;
    sphere.intersect(ray, xs);

    REQUIRE(xs.size == 2);
    REQUIRE(APPROX_EQUAL(xs[0].t, -6.0));
    REQUIRE(APPROX_EQUAL(xs[1].t, -4.0));
}

TEST_CASE("An intersection encapsulates t and object") {
    Sphere sphere;
    Intersections xs;

    Tuple dummyPoint = Tuple::point(0,0,0);
    xs.add(sphere, 3.5, dummyPoint, dummyPoint, dummyPoint);

    REQUIRE(APPROX_EQUAL(xs[0].t, 3.5));
    REQUIRE(xs[0].object == &sphere);
}

TEST_CASE("Precomputing the state of an intersection") {
    Ray ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere sphere;

    Intersections xs;
    sphere.intersect(ray, xs);

    Hit hit = xs[0];

    REQUIRE(hit.object == &sphere);
    REQUIRE(APPROX_EQUAL(hit.t, 4.0));
    REQUIRE(hit.point == Tuple::point(0, 0, -1));
    REQUIRE(hit.eyev == Tuple::vector(0, 0, -1));
    REQUIRE(hit.normalv == Tuple::vector(0, 0, -1));
}

TEST_CASE("The hit, when an intersection occurs on the outside") {
    Ray ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere sphere;

    Intersections xs;
    sphere.intersect(ray, xs);

    Hit hit = xs[0];

    REQUIRE(!hit.inside);
}

TEST_CASE("The hit, when an intersection occurs on the inside") {
    Ray ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Sphere sphere;

    Intersections xs;
    sphere.intersect(ray, xs);

    Hit hit = xs.GetHit();

    REQUIRE(hit.point == Tuple::point(0, 0, 1));
    REQUIRE(hit.eyev == Tuple::vector(0, 0, -1));
    REQUIRE(hit.normalv == Tuple::vector(0, 0, -1));
    REQUIRE(hit.inside);
}