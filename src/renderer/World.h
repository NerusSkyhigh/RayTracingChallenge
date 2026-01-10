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


class World {
public:
    std::vector<PointLight> pointLights;
    std::vector<std::unique_ptr<Shape>> objects;

    World() {}

    bool isShadowed(const Tuple& point, const PointLight& pointLight) const;
    Color shadeHit(const Hit& hit) const;

    static World defaultWorld();

    Color colorAt(const Ray& ray) const {
        Intersections xs;
        for (const auto& object : objects) {
            object->intersect(ray, xs);
        }

        Hit hit = xs.GetHit();
        return shadeHit(hit);
    }

    void addObject(std::unique_ptr<Shape> shape) {
        objects.push_back(std::move(shape));
    }

    void resetLights() {
        pointLights.clear();
    }

    void addPointLight(const PointLight& pointLight) {
        pointLights.push_back(pointLight);
    }

};
