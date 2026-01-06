//
// Created by Gugli on 05/01/2026.
//
#pragma once

#include <memory>
#include <vector>

#include "linalg/Tuple.h"
#include "shapes/shape.h"
#include "PointLight.h"
#include "Color.h"
#include "Material.h"
#include "shapes/Sphere.h"
#include "shapes/Intersections.h"
#include "Ray.h"

class World {
public:
    std::vector<PointLight> pointLights;
    std::vector<std::unique_ptr<Shape>> objects;

    World() {
        pointLights.emplace_back(
            Tuple::point(-10, 10, -10),
            Color(1.0, 1.0, 1.0)
        );

        auto s1 = std::make_unique<Sphere>(
            Material(Color(0.8,1.0,0.6), 0.1, 0.7, 0.2, 200.0)
        );
        objects.push_back(std::move(s1));

        auto s2 = std::make_unique<Sphere>();
        s2->setTransform(Matrix::scaling(0.5, 0.5, 0.5));
        objects.push_back(std::move(s2));
    }

    Intersections intersect(Ray ray) {
        // I need a way to properly intersect a ray with an object
        // Chapter 7
    }

};
