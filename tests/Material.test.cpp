#include <catch2/catch_test_macros.hpp>

#include "renderer/Material.h"

TEST_CASE("The default material") {
    Material mat;

    REQUIRE(mat.color == Color(1.0, 1.0, 1.0));
    REQUIRE(APPROX_EQUAL(mat.ambient, 0.1));
    REQUIRE(APPROX_EQUAL(mat.diffuse, 0.9));
    REQUIRE(APPROX_EQUAL(mat.specular, 0.9));
    REQUIRE(APPROX_EQUAL(mat.shininess, 200.0));
}

TEST_CASE("Lighting with the eye between the light and the surface") {
    Material m;
    Tuple position = Tuple::point(0, 0, 0);

    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv);
    REQUIRE(result == Color(1.9, 1.9, 1.9));
}

TEST_CASE("Lighting with the eye between light and surface, eye offset 45°") {
    Material m;
    Tuple position = Tuple::point(0, 0, 0);

    double sqrt2over2 = std::sqrt(2) / 2;
    Tuple eyev = Tuple::vector(0, sqrt2over2, -sqrt2over2);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv);
    REQUIRE(result == Color(1.0, 1.0, 1.0));
}

TEST_CASE("Lighting with the eye opposite surface, light offset 45°") {
    Material m;
    Tuple position = Tuple::point(0, 0, 0);

    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 10, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv);
    REQUIRE(result == Color(0.7364, 0.7364, 0.7364));
}

TEST_CASE("Lighting with eye in the path of the reflection vector") {
    Material m;
    Tuple position = Tuple::point(0, 0, 0);

    double sqrt2over2 = std::sqrt(2) / 2;
    Tuple eyev = Tuple::vector(0, -sqrt2over2, -sqrt2over2);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 10, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv);
    REQUIRE(result == Color(1.6364, 1.6364, 1.6364));
}

TEST_CASE("Lighting with the light behind the surface") {
    Material m;
    Tuple position = Tuple::point(0, 0, 0);

    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, 10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv);
    REQUIRE(result == Color(0.1, 0.1, 0.1));
}