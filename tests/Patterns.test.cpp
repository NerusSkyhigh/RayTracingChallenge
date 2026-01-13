#include <catch2/catch_test_macros.hpp>

#include "render/Color.h"
#include "scene/pattern/StripePattern.h"
#include "geometry/Sphere.h"
#include "linalg/Tuple.h"

TEST_CASE("A stripe pattern is constant in y") {
    StripePattern pattern(Color::White(), Color::Black());
    REQUIRE(pattern.getColor(Tuple::point(0, 0, 0)) == Color::White());
    REQUIRE(pattern.getColor(Tuple::point(0, 1, 0)) == Color::White());
    REQUIRE(pattern.getColor(Tuple::point(0, 2, 0)) == Color::White());
}

TEST_CASE("A stripe pattern is constant in z") {
    StripePattern pattern(Color::White(), Color::Black());
    REQUIRE(pattern.getColor(Tuple::point(0, 0, 0)) == Color::White());
    REQUIRE(pattern.getColor(Tuple::point(0, 0, 1)) == Color::White());
    REQUIRE(pattern.getColor(Tuple::point(0, 0, 2)) == Color::White());
}

TEST_CASE("A stripe pattern alternates in x") {
    StripePattern pattern(Color::White(), Color::Black());
    REQUIRE(pattern.getColor(Tuple::point(0, 0, 0)) == Color::White());
    REQUIRE(pattern.getColor(Tuple::point(0.9, 0, 0)) == Color::White());
    REQUIRE(pattern.getColor(Tuple::point(1, 0, 0)) == Color::Black());
    REQUIRE(pattern.getColor(Tuple::point(-0.1, 0, 0)) == Color::Black());
    REQUIRE(pattern.getColor(Tuple::point(-1, 0, 0)) == Color::Black());
    REQUIRE(pattern.getColor(Tuple::point(-1.1, 0, 0)) == Color::White());
}
