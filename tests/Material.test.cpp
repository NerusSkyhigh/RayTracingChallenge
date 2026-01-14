#include <catch2/catch_test_macros.hpp>

#include "scene/material/Material.h"
#include "scene/light/PointLight.h"
#include "scene/World.h"
#include "geometry/Sphere.h"
#include "geometry/Intersections.h"
#include "scene/pattern/StripePattern.h"

TEST_CASE("The default material") {
    Material mat;

    Tuple dummyPoint = Tuple::point(0, 0, 0);
    REQUIRE(mat.getColor(dummyPoint) == Color(1.0, 1.0, 1.0));
    REQUIRE(APPROX_EQUAL(mat.getAmbient(), 0.1));
    REQUIRE(APPROX_EQUAL(mat.getDiffuse(), 0.9));
    REQUIRE(APPROX_EQUAL(mat.getSpecular(), 0.9));
    REQUIRE(APPROX_EQUAL(mat.getShininess(), 200.0));
}

TEST_CASE("Lighting with the eye between the light and the surface") {
    Material m;
    Tuple position = Tuple::point(0, 0, 0);

    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv, false);
    REQUIRE(result == Color(1.9, 1.9, 1.9));
}

TEST_CASE("Lighting with the eye between light and surface, eye offset 45°") {
    Material m;
    Tuple position = Tuple::point(0, 0, 0);

    double sqrt2over2 = std::sqrt(2) / 2;
    Tuple eyev = Tuple::vector(0, sqrt2over2, -sqrt2over2);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv, false);
    REQUIRE(result == Color(1.0, 1.0, 1.0));
}

TEST_CASE("Lighting with the eye opposite surface, light offset 45°") {
    Material m;
    Tuple position = Tuple::point(0, 0, 0);

    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 10, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv, false);
    REQUIRE(result == Color(0.7364, 0.7364, 0.7364));
}

TEST_CASE("Lighting with eye in the path of the reflection vector") {
    Material m;
    Tuple position = Tuple::point(0, 0, 0);

    double sqrt2over2 = std::sqrt(2) / 2;
    Tuple eyev = Tuple::vector(0, -sqrt2over2, -sqrt2over2);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 10, -10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv, false);
    REQUIRE(result == Color(1.6364, 1.6364, 1.6364));
}

TEST_CASE("Lighting with the light behind the surface") {
    Material m;
    Tuple position = Tuple::point(0, 0, 0);

    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, 10), Color(1, 1, 1));

    Color result = m.lighting(light, position, eyev, normalv, false);
    REQUIRE(result == Color(0.1, 0.1, 0.1));
}

TEST_CASE("Lighting with the surface in shadow") {
    Material m;
    Tuple position = Tuple::point(0, 0, 0);

    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, -10), Color(1, 1, 1));
    bool in_shadow = true;

    Color result = m.lighting(light, position, eyev, normalv, in_shadow);
    REQUIRE(result == Color(0.1, 0.1, 0.1));
}

TEST_CASE("shadeHits() with an intersection in shadow") {
    // This test would normally be in World.test.cpp, but is included here for completeness
    World world;

    world.addPointLight(
        PointLight(
            Tuple::point(0, 0, -10),
            Color(1, 1, 1)
        )
    );

    // Place a sphere between the point and the light to create a shadow
    auto s1 = std::make_unique<Sphere>();
    world.addObject(std::move(s1));

    auto s2 = std::make_unique<Sphere>();
    s2->setTransform(Matrix::translation(0, 0, 10));
    world.addObject(std::move(s2));

    Ray ray(
        Tuple::point(0, 0, 5),
        Tuple::vector(0, 0, 1)
    );

    Color color = world.colorAt(ray);

    REQUIRE(color == Color(0.1, 0.1, 0.1));
}


TEST_CASE("Lighting with a pattern applied") {
    Material m;
    m.setPattern( std::make_unique<StripePattern>(Color::White(), Color::Black()) );
    m.setAmbient(1);
    m.setDiffuse(0);
    m.setSpecular(0);

    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, -10), Color(1, 1, 1));

    Color c1 = m.lighting(light, Tuple::point(0.9, 0, 0), eyev, normalv, false);
    Color c2 = m.lighting(light, Tuple::point(1.1, 0, 0), eyev, normalv, false);

    REQUIRE(c1 == Color::White());
    REQUIRE(c2 == Color::Black());
}
