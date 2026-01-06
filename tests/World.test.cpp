#include <catch2/catch_test_macros.hpp>

#include "linalg/Matrix.h"
#include "renderer/Material.h"
#include "renderer/World.h"

TEST_CASE("Creating a default world") {
    World w;

    REQUIRE(w.pointLights.size() == 1);
    REQUIRE(w.pointLights[0].position == Tuple::point(-10, 10, -10));
    REQUIRE(w.pointLights[0].intensity == Color(1, 1, 1));

    REQUIRE(w.objects.size() == 2);

    Material expectedMaterial(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200.0);
    REQUIRE(w.objects[0]->GetMaterial() == expectedMaterial);

    REQUIRE(w.objects[1]->GetTransform() == Matrix::scaling(0.5, 0.5, 0.5));
}