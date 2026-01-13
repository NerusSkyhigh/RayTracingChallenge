//
// Created by Gugli on 10/01/2026.
//

#pragma once

#include "linalg/Tuple.h"
#include "linalg/Matrix.h"
#include "geometry/Shape.h"


class Plane : public Shape {
// Locally, the plane lies on the ZX plane (Y=0)
private:
    Matrix transform;
    Matrix itransform;
    Material material;

public:
    Plane() : transform(Matrix::identity(4)), itransform(Matrix::identity(4)) {};
    Plane(Material material) : material(material), transform(Matrix::identity(4)), itransform(Matrix::identity(4)) {};

    void setTransform(const Matrix& m) override {
        this->transform = m;
        this->itransform = m.inverse();
    }

    const Matrix& getTransform() const override {
        return this->transform;
    }

    const Matrix& getInverseTransform() const override {
        return this->itransform;
    }

    void setMaterial(const Material& material) override {
        this->material = material;
    }

    const Material& getMaterial() const override {
        return this->material;
    }

    Color getColorAt(const Tuple& localPoint) const {
        return this->material.getColor(localPoint);
    }

    bool operator==(const Shape& other) const override {
        const Plane* otherSphere = dynamic_cast<const Plane*>(&other);
        if (otherSphere == nullptr) {
            return false;
        }
        bool sameTransform = this->transform == otherSphere->getTransform();
        return sameTransform;
    }

    Tuple NormalAt(const Tuple& worldPoint) const override {
        // In the local space, the normal of a plane is constant
        // and points in the positive Y direction
        Tuple objectNormal = Tuple::vector(0, 1, 0);

        // Transform the normal back to world space
        Matrix localToWorld = this->getInverseTransform();
        Tuple worldNormal = localToWorld.transpose() * objectNormal;
        worldNormal.w = 0; // Ensure it's a vector

        return worldNormal.normalize();
    }

    void intersect(const Ray& ray, Intersections& xs) const override {
        // Transform the ray to object space (Plane's Reference System - PRS)
        Ray rayPRS = ray.transform(this->getInverseTransform());

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
};