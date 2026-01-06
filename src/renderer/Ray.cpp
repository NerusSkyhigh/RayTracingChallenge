//
// Created by Gugli on 02/01/2026.
//

#include "Ray.h"
#include "shapes/Intersections.h"
#include "shapes/Sphere.h"

/*
Intersections Ray::intersect(const Sphere& sphere) const {
    Intersections intersection(sphere);

    Tuple sphereToRay = origin - sphere.origin;

    double a = direction.dot(direction);
    double b = 2 * direction.dot(sphereToRay);
    double c = sphereToRay.dot(sphereToRay) - sphere.radius * sphere.radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return intersection; // No intersections
    }

    double sqrtDiscriminant = std::sqrt(discriminant);
    double t1 = (-b - sqrtDiscriminant) / (2 * a);
    double t2 = (-b + sqrtDiscriminant) / (2 * a);

    intersection.addSolution(t1);
    intersection.addSolution(t2);

    return intersection;
}*/


// [TODO] Handle transformed spheres here
// modifiy the code to handle only unitary spheres centered at the origin
Intersections Ray::intersect(const Sphere& sphere) const {
    Intersections intersection(sphere);

    Tuple sphereToRay = origin - Tuple::point(0, 0, 0); // Sphere at origin

    double a = direction.norm2();
    double b = 2 * direction.dot(sphereToRay);
    double c = sphereToRay.dot(sphereToRay) - 1.0; // Unit sphere radius = 1

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return intersection; // No intersections
    }

    double sqrtDiscriminant = std::sqrt(discriminant);
    double t1 = (-b - sqrtDiscriminant) / (2 * a);
    double t2 = (-b + sqrtDiscriminant) / (2 * a);

    intersection.addSolution(t1);
    intersection.addSolution(t2);

    return intersection;
}