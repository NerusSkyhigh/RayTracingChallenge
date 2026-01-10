//
// Created by Gugli on 10/01/2026.
//

#pragma once

#include "linalg/Tuple.h"
#include "linalg/Matrix.h"
#include "shapes/Shape.h"


class Plane : public Shape {
// Locally, the plane lies on the ZX plane (Y=0)
private:
    Matrix transform;
    Matrix itransform;
    Material material;

public:
    Plane() : transform(Matrix::identity(4)), itransform(Matrix::identity(4)) {};
    Plane(Material material) : material(material), transform(Matrix::identity(4)), itransform(Matrix::identity(4)) {};

    void SetTransform(const Matrix& m) override {
        this->transform = m;
        this->itransform = m.inverse();
    }

    Matrix GetTransform() const override {
        return this->transform;
    }

    Matrix GetInverseTransform() const override {
        return this->itransform;
    }

    void SetMaterial(const Material& material) override {
        this->material = material;
    }

    Material GetMaterial() const override {
        return this->material;
    }

    bool operator==(const Shape& other) const override {
        const Plane* otherSphere = dynamic_cast<const Plane*>(&other);
        if (otherSphere == nullptr) {
            return false;
        }
        bool sameTransform = this->transform == otherSphere->GetTransform();
        return sameTransform;
    }

    Tuple NormalAt(const Tuple& worldPoint) const override {
        // In the local space, the normal of a plane is constant
        // and points in the positive Y direction
        Tuple objectNormal = Tuple::vector(0, 1, 0);

        // Transform the normal back to world space
        Matrix invTrans = this->GetInverseTransform().transpose();
        Tuple worldNormal = invTrans * objectNormal;
        worldNormal.w = 0; // Ensure it's a vector

        return worldNormal.normalize();
    }

    void intersect(const Ray& ray, Intersections& xs) const override {
        // Transform the ray to object space (Plane's Reference System - PRS)
        Ray rayPRS = ray.transform(this->GetInverseTransform());

        // Check if the ray is parallel to the plane ZX
        bool parallelToY = APPROX_EQUAL( std::abs(rayPRS.direction.y), 0);
        if ( parallelToY ) {
            return;
        }

        // Calculate the intersection t value
        double t = -rayPRS.origin.y / rayPRS.direction.y;

        // Find the intersection point in world space
        Tuple ipoint = ray.cast(t);

        Tuple n = this->NormalAt(ipoint);
        Tuple eyev = -ray.direction;

        xs.add(*this, t, ipoint, eyev, n);
    }

bool operator==(int _cpp_par_) const;
};