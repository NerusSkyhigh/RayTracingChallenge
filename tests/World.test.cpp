#include <catch2/catch_test_macros.hpp>

#include "linalg/Matrix.h"
#include "scene/material/Material.h"
#include "geometry/Ray.h"
#include "scene/World.h"
#include "geometry/Intersections.h"

TEST_CASE("Creating a default world") {
    World w = World::defaultWorld();

    REQUIRE(w.pointLights.size() == 1);
    REQUIRE(w.pointLights[0].position == Tuple::point(-10, 10, -10));
    REQUIRE(w.pointLights[0].intensity == Color(1, 1, 1));

    REQUIRE(w.objects.size() == 2);

    Material expectedMaterial(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200.0);
    REQUIRE(w.objects[0]->getMaterial() == expectedMaterial);

    REQUIRE(w.objects[1]->getTransform() == Matrix::scaling(0.5, 0.5, 0.5));
}


TEST_CASE("Shading an intersection") {
    World world = World::defaultWorld();

    Tuple rayOrigin = Tuple::point(0, 0, -5);
    Tuple rayDirection = Tuple::vector(0, 0, 1);
    Ray ray(rayOrigin, rayDirection);

    Intersections xs;
    world.objects[0]->intersect(ray, xs);
    Hit hit = xs.GetHit();

    Color color = world.shadeHit(hit);

    REQUIRE(color == Color(0.38066, 0.47583, 0.2855));
}


TEST_CASE("Shading an intersection from the inside") {
    World w = World::defaultWorld();
    w.pointLights.clear();
    w.pointLights.emplace_back(
        Tuple::point(0, 0.25, 0),
        Color(1, 1, 1)
    );

    Tuple rayOrigin = Tuple::point(0, 0, 0);
    Tuple rayDirection = Tuple::vector(0, 0, 1);
    Ray ray(rayOrigin, rayDirection);

    Intersections xs;
    w.objects[1]->intersect(ray, xs);
    Hit hit = xs.GetHit();

    Color color = w.shadeHit(hit);

    REQUIRE(color == Color(0.90498, 0.90498, 0.90498));
}

TEST_CASE("The color when a ray misses") {
    World world = World::defaultWorld();

    Tuple rayOrigin = Tuple::point(0, 0, -5);
    Tuple rayDirection = Tuple::vector(0, 1, 0);
    Ray ray(rayOrigin, rayDirection);

    Color color = world.colorAt(ray);

    REQUIRE(color == Color(0, 0, 0));
}

TEST_CASE("The color when a ray hits") {
    World world = World::defaultWorld();

    Tuple rayOrigin = Tuple::point(0, 0, -5);
    Tuple rayDirection = Tuple::vector(0, 0, 1);
    Ray ray(rayOrigin, rayDirection);

    Color color = world.colorAt(ray);

    REQUIRE(color == Color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("The color with an intersection behind the ray") {
    World world = World::defaultWorld();

    // Modify the second sphere to be behind the ray
    Material mat1 = world.objects[0]->getMaterial();
    mat1.setAmbient(1.0);
    world.objects[0]->setMaterial(mat1);

    Material mat2 = world.objects[1]->getMaterial();
    mat2.setAmbient(1.0);
    world.objects[1]->setMaterial(mat2);

    Tuple rayOrigin = Tuple::point(0, 0, 0.75);
    Tuple rayDirection = Tuple::vector(0, 0, -1);
    Ray ray(rayOrigin, rayDirection);

    Color color = world.colorAt(ray);

    Tuple dummyPoint = Tuple::point(0, 0, 0);
    REQUIRE(color == world.objects[1]->getMaterial().getColor(dummyPoint));
}

TEST_CASE("There is no shadow when nothing is collinear with point and light") {
    World world = World::defaultWorld();
    Tuple point = Tuple::point(0, 10, 0);

    REQUIRE_FALSE(world.isShadowed(point, world.pointLights[0]));
}

TEST_CASE("The shadow when an object is between the point and the light") {
    World world = World::defaultWorld();
    Tuple point = Tuple::point(10, -10, 10);

    REQUIRE(world.isShadowed(point, world.pointLights[0]));
}

TEST_CASE("There is no shadow when an object is behind the light") {
    World world = World::defaultWorld();
    Tuple point = Tuple::point(-20, 20, -20);

    REQUIRE_FALSE(world.isShadowed(point, world.pointLights[0]));
}

TEST_CASE("There is no shadow when an object is behind the point") {
    World world = World::defaultWorld();
    Tuple point = Tuple::point(-2, 2, -2);

    REQUIRE_FALSE(world.isShadowed(point, world.pointLights[0]));
}