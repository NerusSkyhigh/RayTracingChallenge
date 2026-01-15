//
// Created by Gugli on 04/01/2026.
//


#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <chrono>
#include <iostream>

#include "linalg/Tuple.h"
#include "linalg/Matrix.h"
#include "linalg/ViewTransform.h"
#include "render/Camera.h"
#include "render/Canvas.h"
#include "scene/material/Material.h"
#include "scene/light/PointLight.h"
#include "scene/World.h"
#include "geometry/Plane.h"
#include "geometry/Sphere.h"
#include "scene/pattern/CheckerPattern.h"
#include "scene/pattern/GradientPattern.h"
#include "scene/pattern/StripePattern.h"



int main() {

    auto checker = std::make_unique<CheckerPattern>( Color::White(), Color::Black() );
    checker->setTransform( Matrix::scaling(1./8., 1, 1) );
    auto monoGray = std::make_unique<Monocromatic>( Color::Gray() );
    auto gradientChecker = std::make_unique<GradientPattern>( std::move(checker), std::move(monoGray) );
    gradientChecker->setTransform( Matrix::rotationY(-M_PI / 2) *
        Matrix::scaling(8, 1, 1) );

    Material floorMaterial;
    floorMaterial.setPattern(gradientChecker->clone() );
    floorMaterial.setSpecular(0);

    std::unique_ptr<Plane> floor = std::make_unique<Plane>();
    floor->setTransform(Matrix::translation(0, 0, 0));
    floor->setMaterial(floorMaterial);

    auto zebra = std::make_unique<StripePattern>( Color::Black(), Color::White() );
    Material backgroundMaterial;
    backgroundMaterial.setPattern(zebra->clone() );
    backgroundMaterial.setSpecular(0);

    std::unique_ptr<Plane> background = std::make_unique<Plane>();
    background->setTransform(
        Matrix::translation(0, 0, 5) *
        Matrix::rotationX(M_PI / 2)
    );
    background->setMaterial(backgroundMaterial);




    Material middleMaterial;
    middleMaterial.setColor(Color::Green());
    middleMaterial.setDiffuse(0.7);
    middleMaterial.setSpecular(0.3);

    auto middle = std::make_unique<Sphere>();
    middle->setTransform(Matrix::translation(-0.5, 1, 0.5));
    middle->setMaterial(middleMaterial);


    auto btr = std::make_unique<GradientPattern>( Color::Blue(), Color::Red() );
    btr->setTransform(Matrix::rotationZ(M_PI/4)*
        Matrix::scaling(0.1, 0.1, 0.1) );

    auto rtb = std::make_unique<Monocromatic>(Color::White());

    auto rotatedZebra = std::make_unique<StripePattern>( std::move(btr), std::move(rtb) );
    rotatedZebra->setTransform( Matrix::rotationX(M_PI / 4) *
                                         Matrix::rotationZ(M_PI / 4) *
                                         Matrix::scaling(0.1, 0.1, 0.1) );

    Material rightMaterial;
    rightMaterial.setPattern(std::move(rotatedZebra));
    //rightMaterial.setColor( Color(0.5, 1, 0.1) );
    rightMaterial.setDiffuse(0.7);
    rightMaterial.setDiffuse(0.3);

    auto right = std::make_unique<Sphere>();
    right->setTransform(
        Matrix::translation(1.5, 0.5, -0.5) *
        Matrix::scaling(0.5, 0.5, 0.5)
    );
    right->setMaterial(rightMaterial);





    auto gradient = std::make_unique<GradientPattern>( Color::White(), Color::Black() );
    Material leftMaterial;
    leftMaterial.setPattern(std::move(gradient) );
    leftMaterial.setDiffuse(0.7);
    leftMaterial.setSpecular(0.3);

    auto left = std::make_unique<Sphere>();
    left->setTransform(
        Matrix::translation(-1.5, 0.33, -0.75) *
        Matrix::scaling(0.33, 0.33, 0.33)
    );
    left->setMaterial(leftMaterial);



    PointLight light(
        Tuple::point(-10, 10, -10),
        Color(1, 1, 1)
    );



    World world;
    world.addObject(std::move(floor) );
    world.addObject(std::move(background));

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

    auto now = std::chrono::high_resolution_clock::now();
    Canvas image = camera.render(world);

    auto later = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = later - now;
    std::cout << "Render time: " << elapsed.count() << " seconds." << std::endl;

    image.ToPPMFile("../cp10_Patterns.ppm");

    return 0;
}