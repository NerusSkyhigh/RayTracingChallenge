#include "../src/renderer/Ray.h"
#include "catch2/catch_test_macros.hpp"

#include "../src/shapes/Sphere.h"

TEST_CASE("A sphere default transform") {
    Sphere sphere;
    Matrix identity = Matrix::identity(4);
    REQUIRE(sphere.transform == identity);
}

TEST_CASE("Changing a sphere's transform") {
    Sphere s;
    Matrix translation = Matrix::translation(2, 3, 4);
    s.setTransform(translation);
    REQUIRE(s.transform == translation);
}

TEST_CASE("Intersecting a scaled sphere with a ray") {
    Tuple rayOrigin = Tuple::point(0, 0, -5);
    Tuple rayDirection = Tuple::vector(0, 0, 1);
    Ray ray(rayOrigin, rayDirection);

    Sphere sphere;
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

    Sphere sphere;
    sphere.setTransform(Matrix::translation(5, 0, 0));

    Intersections intersection = ray.transform( sphere.transform.inverse()).intersect(sphere);

    REQUIRE(intersection.size == 0);
}

TEST_CASE("Computing the normal on a sphere at a point on the x axis") {
    Sphere s;
    Tuple p = Tuple::point(1, 0, 0);

    Tuple n = s.NormalAt(p);
    REQUIRE(n == Tuple::vector(1, 0, 0));
}

TEST_CASE("Computing the normal on a sphere at a point on the y axis") {
    Tuple p = Tuple::point(0, 1, 0);
    Sphere sphere;
    Tuple n = sphere.NormalAt(p);

    REQUIRE(n == Tuple::vector(0, 1, 0));
}

TEST_CASE("Computing the normal on a sphere at a point on the z axis") {
    Tuple p = Tuple::point(0, 0, 1);
    Sphere sphere;
    Tuple n = sphere.NormalAt(p);

    REQUIRE(n == Tuple::vector(0, 0, 1));
}

TEST_CASE("Computing the normal on a sphere at a nonaxial point") {
    double val = std::sqrt(3) / 3;
    Tuple p = Tuple::point(val, val, val);
    Sphere sphere;
    Tuple n = sphere.NormalAt(p);

    REQUIRE(n == Tuple::vector(val, val, val));
}

TEST_CASE("The normal is a normalized vector") {
    double val = std::sqrt(3) / 3;
    Tuple p = Tuple::point(val, val, val);
    Sphere sphere;
    Tuple n = sphere.NormalAt(p);

    REQUIRE(n == n.normalize());
}

TEST_CASE("A sphere has a default material") {
    Sphere s;
    Material m;
    REQUIRE(s.material == m);
}

TEST_CASE("A sphere may be assigned a material") {
    Sphere s;
    Material m;
    m.ambient = 1.0;
    s.SetMaterial(m);
    REQUIRE(s.material == m);
}