//
// Created by Gugli on 03/01/2026.
//
#pragma once
#include "linalg/Tuple.h"
#include "linalg/Matrix.h"
#include "Shape.h"
#include "renderer/Material.h"


/**@brief Represents a sphere in 3D space
 * To change the sphere's position, scale, or rotation, use the transformation matrix
 */
class Sphere : public Shape {
private:
    Matrix itransform;

public:
    Tuple origin; // [TODO] Set this to (0,0,0)
    Matrix transform;
    Material material;

    Sphere(): origin(Tuple::point(0,0,0)), transform(Matrix::identity(4)), itransform(Matrix::identity(4)) {}

    Sphere(const Tuple origin) : origin(origin), transform(Matrix::identity(4)), itransform(Matrix::identity(4)) {}

    Sphere(Material material) : origin(Tuple::point(0, 0, 0)), material(material), transform(Matrix::identity(4)), itransform(Matrix::identity(4)) {}


    const bool operator==(const Sphere&) const {
        bool sameOrigin = this->origin == origin;
        bool sameTransform = this->transform == transform;
        return sameOrigin && sameTransform;
    }

    void SetTransform(const Matrix& m) override {
        this->transform = m;
        this->itransform = m.inverse();
    }

    void addTransform(const Matrix& m) {
        Matrix newTransform = m * this->transform;
        SetTransform(newTransform);
    }

    void resetTransform() {
        SetTransform(Matrix::identity(4));
    }

    Matrix GetTransform() const override {
        return this->transform;
    }

    Matrix GetInverseTransform() const override {
        return this->itransform;
    }

    /**@brief Computes the normal vector at point p on the unit sphere centered at the origin
     * @param p
     * @return
     */
    Tuple NormalAt(Tuple p) const {
        // I have to subtract the sphere's center from p, even though
        // it's the origin because p is a point and not a vector.
        // The difference between two points gives the correct
        // value of w for a vector.

        Tuple n = p - Tuple::point(0, 0, 0);
        Matrix transform = this->transform.inverse().transpose();

        return (transform * n).normalize();
    }

    void SetMaterial(const Material& m) override {
        this->material = m;
    }

    Material GetMaterial() const override {
        return this->material;
    }

    /**@brief Computes the intersections of a ray with this sphere
     * @param ray The ray to intersect with the sphere
     * @param xs The Intersections object to store the results
     */
    void intersect(const Ray& ray, Intersections& xs) const override;

};
