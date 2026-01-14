#include <catch2/catch_test_macros.hpp>

#include "linalg/Tuple.h"
#include "scene/light/PointLight.h"

TEST_CASE("A point light has a position and an intensity") {
    Tuple position = Tuple::point(1, 1, 1);
    Color intensity = Color(1, 1, 1);
    PointLight light(position, intensity);

    REQUIRE(light.position == position);
    REQUIRE(light.intensity == intensity);
}