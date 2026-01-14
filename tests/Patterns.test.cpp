#include <catch2/catch_test_macros.hpp>

#include "render/Color.h"
#include "scene/pattern/StripePattern.h"
#include "scene/pattern/RingPattern.h"
#include "scene/pattern/CheckerPattern.h"
#include "scene/pattern/Monocromatic.h"
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

TEST_CASE("Stripes with an object transformation") {
    auto pattern = std::make_unique<StripePattern>(Color::White(), Color::Black());

    Material material;
    material.setPattern(std::move(pattern) );

    Sphere sphere(material);
    sphere.setTransform(Matrix::scaling(2, 2, 2));

    Tuple point = Tuple::point(1.5, 0, 0);
    Color c = sphere.getWorldColor(point);

    REQUIRE(c == Color::White());
}


TEST_CASE("Stripes with a pattern transformation") {
    auto pattern = std::make_unique<StripePattern>(Color::White(), Color::Black());
    pattern->setTransform(Matrix::scaling(2, 2, 2));

    Material material;
    material.setPattern(std::move(pattern) );

    Sphere sphere(material);

    Tuple point = Tuple::point(1.5, 0, 0);
    Color c = sphere.getWorldColor(point);

    REQUIRE(c == Color::White());
}

TEST_CASE("Stripes with both an object and a pattern transformation") {
    auto pattern = std::make_unique<StripePattern>(Color::White(), Color::Black());
    pattern->setTransform(Matrix::scaling(2, 2, 2));

    Material material;
    material.setPattern(std::move(pattern) );

    Sphere sphere(material);
    sphere.setTransform(Matrix::scaling(2, 2, 2));

    Tuple point = Tuple::point(1.5, 0, 0);
    Color c = sphere.getWorldColor(point);

    REQUIRE(c == Color::White());
}

TEST_CASE("The default pattern transformation") {
    Monocromatic pattern(Color::White());
    REQUIRE(pattern.getTransform() == Matrix::identity(4));
}

TEST_CASE("Assigning a transformation to a pattern") {
    StripePattern pattern(Color::White(), Color::Black());
    pattern.setTransform(Matrix::translation(1, 2, 3));
    REQUIRE(pattern.getTransform() == Matrix::translation(1, 2, 3));
}

TEST_CASE("A gradient linearly interpolates between colors") {
    StripePattern pattern(Color::White(), Color::Black());

    Color c = pattern.getColor(Tuple::point(0, 0, 0));
    REQUIRE(c == Color::White());
}

TEST_CASE("A ring should extend in both x and z") {
    RingPattern pattern(Color::White(), Color::Black());

    REQUIRE( pattern.getColor( Tuple::point(0, 0, 0) ) == Color::White());
    REQUIRE( pattern.getColor( Tuple::point(1, 0, 0) ) == Color::Black());
    REQUIRE( pattern.getColor( Tuple::point(0, 0, 1) ) == Color::Black());

    double sqrt2h = sqrt(2)/2;
    REQUIRE( pattern.getColor( Tuple::point(sqrt2h, 0, sqrt2h) ) == Color::Black());

}

TEST_CASE("Checkers should repeat in x") {
    CheckerPattern pattern(Color::White(), Color::Black());

    REQUIRE( pattern.getColor( Tuple::point(0, 0, 0) ) == Color::White());
    REQUIRE( pattern.getColor( Tuple::point(0.99, 0, 0) ) == Color::White());
    REQUIRE( pattern.getColor( Tuple::point(1.01, 0, 0) ) == Color::Black());
}

TEST_CASE("Checkers should repeat in y") {
    CheckerPattern pattern(Color::White(), Color::Black());

    REQUIRE( pattern.getColor( Tuple::point(0, 0, 0) ) == Color::White());
    REQUIRE( pattern.getColor( Tuple::point(0, 0.99, 0) ) == Color::White());
    REQUIRE( pattern.getColor( Tuple::point(0, 1.01,  0) ) == Color::Black());
}

TEST_CASE("Checkers should repeat in z") {
    CheckerPattern pattern(Color::White(), Color::Black());

    REQUIRE( pattern.getColor( Tuple::point(0, 0, 0) ) == Color::White());
    REQUIRE( pattern.getColor( Tuple::point(0, 0, 0.99) ) == Color::White());
    REQUIRE( pattern.getColor( Tuple::point(0, 0, 1.01) ) == Color::Black());
}