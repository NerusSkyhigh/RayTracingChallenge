//
// Created by Gugli on 04/01/2026.
//


#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>

#include "linalg/Tuple.h"
#include "linalg/Matrix.h"
#include "linalg/ViewTransform.h"
#include "renderer/Camera.h"
#include "renderer/Canvas.h"
#include "renderer/Material.h"
#include "renderer/PointLight.h"
#include "renderer/World.h"
#include "shapes/Sphere.h"



int main() {
    Material floorMaterial;
    floorMaterial.color = Color(1, 0.9, 0.9);
    floorMaterial.specular = 0;


    std::unique_ptr<Sphere> floor = std::make_unique<Sphere>();
    floor->SetTransform(Matrix::scaling(10, 0.01, 10));
    floor->SetMaterial(floorMaterial);


    auto leftWall = std::make_unique<Sphere>();
    leftWall->SetTransform(
        Matrix::translation(0, 0, 5) *
        Matrix::rotationY(-M_PI / 4) *
        Matrix::rotationX(M_PI / 2) *
        Matrix::scaling(10, 0.01, 10)
    );
    leftWall->SetMaterial(floorMaterial);


    auto rightWall = std::make_unique<Sphere>();
    rightWall->SetTransform(
        Matrix::translation(0, 0, 5) *
        Matrix::rotationY(M_PI / 4) *
        Matrix::rotationX(M_PI / 2) *
        Matrix::scaling(10, 0.01, 10)
    );
    rightWall->SetMaterial(floorMaterial);


    Material middleMaterial;
    middleMaterial.color = Color(0.1, 1, 0.5);
    middleMaterial.diffuse = 0.7;
    middleMaterial.specular = 0.3;

    auto middle = std::make_unique<Sphere>();
    middle->SetTransform(Matrix::translation(-0.5, 1, 0.5));
    middle->SetMaterial(middleMaterial);


    Material rightMaterial;
    rightMaterial.color = Color(0.5, 1, 0.1);
    rightMaterial.diffuse = 0.7;
    rightMaterial.specular = 0.3;

    auto right = std::make_unique<Sphere>();
    right->SetTransform(
        Matrix::translation(1.5, 0.5, -0.5) *
        Matrix::scaling(0.5, 0.5, 0.5)
    );
    right->SetMaterial(rightMaterial);


    Material leftMaterial;
    leftMaterial.color = Color(1, 0.8, 0.1);
    leftMaterial.diffuse = 0.7;
    leftMaterial.specular = 0.3;

    auto left = std::make_unique<Sphere>();
    left->SetTransform(
        Matrix::translation(-1.5, 0.33, -0.75) *
        Matrix::scaling(0.33, 0.33, 0.33)
    );
    left->SetMaterial(leftMaterial);



    PointLight light(
        Tuple::point(-10, 10, -10),
        Color(1, 1, 1)
    );



    World world;
    world.addObject(std::move(floor) );
    world.addObject(std::move(leftWall) );
    world.addObject(std::move(rightWall) );

    world.addObject(std::move(middle));
    world.addObject(std::move(right));
    world.addObject(std::move(left));

    world.resetLights();
    world.addPointLight(light);


    Camera camera(800, 400, M_PI / 3);
    ViewTransform viewTransform = ViewTransform(
        Tuple::point(0, 1.5, -5),
        Tuple::point(0, 1, 0),
        Tuple::vector(0, 1, 0)
    );
    camera.SetViewTransform(viewTransform);

    Canvas image = camera.render(world);
    image.ToPPMFile("../cp7_Scene.ppm");

    return 0;
}