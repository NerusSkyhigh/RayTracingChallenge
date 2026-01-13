// Color.test.cpp
// Created by Guglielmo Grillo on 30/12/2025.
//
#include <catch2/catch_test_macros.hpp>
#include "../src/render/Color.h"

TEST_CASE("Color equality with floating point precision") {
    Color c1 = Color(0.1 + 0.2, 0.3, 0.4);
    Color c2 = Color(0.3, 0.3, 0.4);
    REQUIRE(c1 == c2);
}

TEST_CASE("Adding colors") {
    Color c1 = Color(0.9, 0.6, 0.75);
    Color c2 = Color(0.7, 0.1, 0.25);
    Color result = c1 + c2;
    Color expected = Color(1.6, 0.7, 1.0);
    REQUIRE(result == expected);
}

TEST_CASE("Subtracting colors") {
    Color c1 = Color(0.9, 0.6, 0.75);
    Color c2 = Color(0.7, 0.1, 0.25);
    Color result = c1 - c2;
    REQUIRE(result == Color(0.2, 0.5, 0.5));
}

TEST_CASE("Multiplying color by scalar") {
    Color c = Color(0.2, 0.3, 0.4);
    double scalar = 2.0;
    Color result = c * scalar;
    REQUIRE(result == Color(0.4, 0.6, 0.8));
}

TEST_CASE("Dividing color by scalar") {
    Color c = Color(0.4, 0.6, 0.8);
    double scalar = 2.0;
    Color result = c / scalar;
    REQUIRE(result == Color(0.2, 0.3, 0.4));
}

TEST_CASE("Hadamard product of colors") {
    Color c1 = Color(1.0, 0.2, 0.4);
    Color c2 = Color(0.9, 1.0, 0.1);
    Color result = c1.hadamard(c2);
    REQUIRE(result == Color(0.9, 0.2, 0.04));
}