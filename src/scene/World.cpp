//
// Created by Gugli on 05/01/2026.
//

#include "linalg/macros.h"
#include "World.h"

#include "../render/Color.h"
#include "../geometry/Intersections.h"
#include "../geometry/Shape.h"
#include "../geometry/Sphere.h"

bool World::isShadowed(const Tuple& point, const PointLight& pointLight) const {

    Tuple vectorToLight = pointLight.position - point;
    double distanceToLight2 = vectorToLight.norm2();

    Ray ray = Ray(point, vectorToLight.normalize());

    Intersections xs;

    // This check that at least one object is between the point and one the lights
    // [TODO] Handle multiple lights properly by checking each light separately
    // and return a list of shadowed lights.
    for (const auto& object : objects) {

        // [TODO] A single intersection is enough to determine if the point is in shadow,
        // so we could optimize have a function analogous to Shape->intersect that stops
        // at the first hit.
        object->intersect(ray, xs);
    }
    Hit hit = xs.GetHit();

    if (hit.valid && SQUARE(hit.t) <= distanceToLight2) {
        // There is an object between the point and the light
        return true;
    }
    return false; // No object is blocking the light


}

Color World::shadeHit(const Hit& hit) const {
    Color color = Color::Black(); // Start with black

    if (!hit.valid) {
        return color;
    }

    Material mat = hit.object->getMaterial();

    // Accumulate the contribution from each light source
    for (const auto& light : pointLights) {
        bool inShadow = this->isShadowed(hit.overPoint, light);

        color += mat.lighting(
            light,
            hit.overPoint,
            hit.eyev,
            hit.normalv,
            inShadow
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
    m1.setColor( Color(0.8, 1.0, 0.6) );
    m1.setDiffuse(0.7);
    m1.setSpecular(0.2);

    auto s1 = std::make_unique<Sphere>();
    s1->setMaterial(m1);
    w.objects.push_back(std::move(s1));


    // Add the second sphere with scaling transformation
    auto s2 = std::make_unique<Sphere>();
    s2->setTransform(Matrix::scaling(0.5, 0.5, 0.5));
    w.objects.push_back(std::move(s2));

    return w;
}