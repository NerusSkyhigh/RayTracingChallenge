//
// Created by Gugli on 04/01/2026.
//

#define _USE_MATH_DEFINES

#include <iostream>

#include <cmath>
#include <numbers>
#include <fstream>

#include "linalg/Tuple.h"
#include "linalg/Matrix.h"
#include "renderer/Canvas.h"
#include "renderer/Ray.h"
#include "renderer/Material.h"
#include "renderer/PointLight.h"
#include "renderer/World.h"
#include "renderer/Camera.h"
#include "shapes/Sphere.h"


int main() {
    Material material;
    material.color = Color(1, 0.2, 1);
    std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>();
    sphere->SetMaterial(material);

    // Add a light
    PointLight light(
        Tuple::point(-10, 15, -10),
        Color(1, 1, 1)
    );

    World world;
    world.addObject(std::move(sphere));
    world.addPointLight(light);

    Camera camera(512, 512, M_PI/3);
    camera.SetViewTransform(
        ViewTransform(
            Tuple::point(0, 0, -2.5),
            Tuple::point(0, 0, 0),
            Tuple::vector(0, 1, 0)
        )
    );

    Canvas image = camera.render(world);
    image.ToPPMFile("../cp6_LightingSphereCameraVersion.ppm");


    return 0;
}