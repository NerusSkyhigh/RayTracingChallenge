//
// Created by Gugli on 04/01/2026.
//


#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>

#include "linalg/Matrix.h"
#include "renderer/Camera.h"
#include "renderer/Canvas.h"
#include "renderer/Material.h"
#include "shapes/Sphere.h"



int main() {
    World world;

    std::unique_ptr<Sphere> floor = std::make_unique<Sphere>();
    floor->SetTransform(Matrix::scaling(10, 0.01, 10));
    Material floorMaterial;
    floorMaterial.color = Color(1, 0.9, 0.9);
    floorMaterial.specular = 0;
    floor->SetMaterial(floorMaterial);
    world.addObject(std::move(floor) );


    auto leftWall = std::make_unique<Sphere>();
    leftWall->SetTransform(
        Matrix::translation(0, 0, 5) *
        Matrix::rotationY(-M_PI / 4) *
        Matrix::rotationX(M_PI / 2) *
        Matrix::scaling(10, 0.01, 10)
    );
    leftWall->SetMaterial(floorMaterial);
    world.addObject(std::move(leftWall) );

    auto rightWall = std::make_unique<Sphere>();
    rightWall->SetTransform(
        Matrix::translation(0, 0, 5) *
        Matrix::rotationY(M_PI / 4) *
        Matrix::rotationX(M_PI / 2) *
        Matrix::scaling(10, 0.01, 10)
    );
    rightWall->SetMaterial(floorMaterial);
    world.addObject(std::move(rightWall) );

    auto middle = std::make_unique<Sphere>();
    middle->SetTransform(Matrix::translation(-0.5, 1, 0.5));
    Material middleMaterial;
    middleMaterial.color = Color(0.1, 1, 0.5);
    middleMaterial.diffuse = 0.7;
    middleMaterial.specular = 0.3;
    middle->SetMaterial(middleMaterial);
    world.addObject(std::move(middle));

    auto right = std::make_unique<Sphere>();
    right->SetTransform(
        Matrix::translation(1.5, 0.5, -0.5) *
        Matrix::scaling(0.5, 0.5, 0.5)
    );
    Material rightMaterial;
    rightMaterial.color = Color(0.5, 1, 0.1);
    rightMaterial.diffuse = 0.7;
    rightMaterial.specular = 0.3;
    right->SetMaterial(rightMaterial);
    world.addObject(std::move(right));

    auto left = std::make_unique<Sphere>();
    left->SetTransform(
        Matrix::translation(-1.5, 0.33, -0.75) *
        Matrix::scaling(0.33, 0.33, 0.33)
    );
    Material leftMaterial;
    leftMaterial.color = Color(1, 0.8, 0.1);
    leftMaterial.diffuse = 0.7;
    leftMaterial.specular = 0.3;
    left->SetMaterial(leftMaterial);
    world.addObject(std::move(left));

    Tuple lightOrigin = Tuple::point(-10, 10, -10);
    Color lightColor = Color(1, 1, 1);
    PointLight light(lightOrigin, lightColor);
    world.resetLights();
    world.addPointLight(light);

    Camera camera(600, 300, M_PI / 3);
    ViewTransform viewTransform = ViewTransform(
        Tuple::point(0, 1.5, -5),
        Tuple::point(0, 1, 0),
        Tuple::vector(0, 1, 0)
    );
    camera.SetViewTransform(viewTransform);

    Canvas image = camera.render(world);
    image.ToPPMFile("../cp7_Scene.ppm");
    printf("Finish saving");



    return 0;
}