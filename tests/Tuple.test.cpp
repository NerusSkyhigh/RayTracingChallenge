// Tuple.test.cpp
// Created by Guglielmo Grillo on 30/12/2025.
//
#include <catch2/catch_test_macros.hpp>
#include "tuple.h"

TEST_CASE("A tuple with w=1 is a point") {
    Tuple p = Tuple(4.3, -4.2, 3.1, 1.);
    REQUIRE(p.is_point());
    REQUIRE(!p.is_vector());

    Tuple p2 = Tuple::point(4.3, -4.2, 3.1);
    REQUIRE(p2.is_point());
    REQUIRE(!p2.is_vector());
}

TEST_CASE("A tupple with w=0 is a vector") {
    Tuple v = Tuple(4.3, -4.2, 3.1, 0);
    REQUIRE(!v.is_point());
    REQUIRE(v.is_vector());

    Tuple v2 = Tuple::vector(4.3, -4.2, 3.1);;
    REQUIRE(!v2.is_point());
    REQUIRE(v2.is_vector());
}

TEST_CASE("Adding two vectors") {
    Tuple v1 = Tuple::vector(3, -2, 5);
    Tuple v2 = Tuple::vector(-2, 3, 1);
    Tuple result = v1 + v2;
    REQUIRE(result == Tuple::vector(1, 1, 6));
}

TEST_CASE("Subtracting two points") {
    Tuple p1 = Tuple::point(3, 2, 1);
    Tuple p2 = Tuple::point(5, 6, 7);
    Tuple result = p1 - p2;
    REQUIRE(result == Tuple::vector(-2, -4, -6));
}

TEST_CASE("Subtracting a vector from a point") {
    Tuple p = Tuple::point(3, 2, 1);
    Tuple v = Tuple::vector(5, 6, 7);
    Tuple result = p - v;
    REQUIRE(result == Tuple::point(-2, -4, -6));
}

TEST_CASE("Subtracting two vectors") {
    Tuple v1 = Tuple::vector(3, 2, 1);
    Tuple v2 = Tuple::vector(5, 6, 7);
    Tuple result = v1 - v2;
    REQUIRE(result == Tuple::vector(-2, -4, -6));
}

TEST_CASE("Negating a ") {
    Tuple a = Tuple(1, -2, 3, -4);
    Tuple result = -a;
    REQUIRE(result == Tuple(-1, 2, -3, 4));
}

TEST_CASE("Multiplying a tuple by a scalar") {
    Tuple a = Tuple(1, -2, 3, -4);
    Tuple result = a * 3.5;
    REQUIRE(result == Tuple(3.5, -7, 10.5, -14));
}

TEST_CASE("Multiplying a tuple by a fraction") {
    Tuple a = Tuple(1, -2, 3, -4);
    Tuple result = a * 0.5;
    REQUIRE(result == Tuple(0.5, -1, 1.5, -2));
}

TEST_CASE("Dividing a tuple by a scalar") {
    Tuple a = Tuple(1, -2, 3, -4);
    Tuple result = a / 2;
    REQUIRE(result == Tuple(0.5, -1, 1.5, -2));
}

TEST_CASE("Normalizing the vector (4, 0, 0) gives (1, 0, 0)") {
    Tuple v = Tuple::vector(4, 0, 0);
    Tuple result = v.normalize();
    REQUIRE(result == Tuple::vector(1, 0, 0));
}

TEST_CASE("Cross product") {
    Tuple a = Tuple::vector(1, 2, 3);
    Tuple b = Tuple::vector(2, 3, 4);
    Tuple result1 = a.cross(b);
    Tuple result2 = b.cross(a);
    REQUIRE(result1 == Tuple::vector(-1, 2, -1));
    REQUIRE(result2 == -result1);
}