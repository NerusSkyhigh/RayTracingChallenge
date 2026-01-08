//
// Created by Gugli on 05/01/2026.
//

#include "World.h"

#include "Color.h"
#include "shapes/Intersections.h"
#include "shapes/Shape.h"
#include "shapes/Sphere.h"

Color World::shadeHit(const Hit& hit) const {
    Color color = Color::Black(); // Start with black

    if (!hit.valid) {
        return color;
    }

    Material mat = hit.object->GetMaterial();

    // Accumulate the contribution from each light source
    for (const auto& light : pointLights) {
        color += mat.lighting(
            light,
            hit.point,
            hit.eyev,
            hit.normalv
        );
    }

    return color;
}

World World::defaultWorld() {
    World w;

    // Add a default light source
    Tuple lightOrigin = Tuple::point(-10, 10, -10);
    Color lightColor = Color(1, 1, 1);
    PointLight defaultLight(lightOrigin, lightColor);
    w.pointLights.emplace_back(defaultLight);

    // Add the first sphere with specific material
    Material m1;
    m1.color = Color(0.8, 1.0, 0.6);
    m1.diffuse = 0.7;
    m1.specular = 0.2;

    auto s1 = std::make_unique<Sphere>();
    s1->SetMaterial(m1);
    w.objects.push_back(std::move(s1));


    // Add the second sphere with scaling transformation
    auto s2 = std::make_unique<Sphere>();
    s2->SetTransform(Matrix::scaling(0.5, 0.5, 0.5));
    w.objects.push_back(std::move(s2));

    return w;
}