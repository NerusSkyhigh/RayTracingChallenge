#include <catch2/catch_test_macros.hpp>

#include "../src/geometry/Plane.h"
#include "../src/geometry/Intersections.h"

TEST_CASE("The normal of a plane is constant everywhere") {
    Plane p;
    Tuple n1 = p.NormalAt(Tuple::point(0, 0, 0));
    Tuple n2 = p.NormalAt(Tuple::point(10, 0, -10));
    Tuple n3 = p.NormalAt(Tuple::point(-5, 0, 150));

    REQUIRE(n1 == Tuple::vector(0, 1, 0));
    REQUIRE(n2 == Tuple::vector(0, 1, 0));
    REQUIRE(n3 == Tuple::vector(0, 1, 0));
}

TEST_CASE("Intersecting a ray parallel to the plane") {
    Plane p;
    Ray ray(Tuple::point(0, 10, 0), Tuple::vector(0, 0, 1)); // Parallel to the plane

    Intersections xs;
    p.intersect(ray, xs);

    REQUIRE(xs.getSize() == 0);
}

TEST_CASE("A ray intersecting the plane from above") {
    Plane p;
    Ray ray(
        Tuple::point(0, 1, 0),
        Tuple::vector(0, -1, 0)
    );

    Intersections xs;
    p.intersect(ray, xs);

    REQUIRE(xs.getSize() == 1);
    REQUIRE( APPROX_EQUAL(xs[0].t, 1.0) );
    REQUIRE(*xs[0].object == p);
}