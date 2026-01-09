//
// Created by Gugli on 03/01/2026.
//

#include "Sphere.h"
#include "renderer/Ray.h"
#include "Intersections.h"
#include "linalg/Tuple.h"

void Sphere::intersect(const Ray& ray, Intersections& xs) const {
    // Transform the ray to object space (Sphere's Reference System - SRS)
    Ray raySRS = ray.transform(this->GetInverseTransform());

    Tuple sphereToRay = raySRS.origin - Tuple::point(0, 0, 0); // Sphere at origin

    double a = raySRS.direction.norm2();
    double b = 2 * raySRS.direction.dot(sphereToRay);
    double c = sphereToRay.dot(sphereToRay) - 1.0; // Unit sphere radius = 1

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return; // No intersections
    }

    double sqrtDiscriminant = std::sqrt(discriminant);
    double t1 = (-b - sqrtDiscriminant) / (2 * a);
    double t2 = (-b + sqrtDiscriminant) / (2 * a);

    // Find the intersection points in world space
    Tuple ipoint1 = ray.cast(t1);
    Tuple ipoint2 = ray.cast(t2);

    Tuple n1 = this->NormalAt(ipoint1);
    Tuple n2 = this->NormalAt(ipoint2);

    // Vector from intersection to eye; it goes in the opposite direction of the ray
    // I think I should not normalize the vector as it encodes scaling information
    Tuple eyev = -ray.direction;

    xs.add(*this, t1, ipoint1, eyev, n1 );
    xs.add(*this, t2, ipoint2, eyev, n2 );
}