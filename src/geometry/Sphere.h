//
// Created by Gugli on 03/01/2026.
//
#pragma once
#include "linalg/Tuple.h"
#include "linalg/Matrix.h"
#include "Shape.h"
#include "scene/material/Material.h"


/**@brief Represents a sphere in 3D space
 * To change the sphere's position, scale, or rotation, use the transformation matrix
 */
class Sphere : public Shape {
private:
    Matrix transform;
    Matrix itransform;
    Material material;

public:
    Sphere():   transform(Matrix::identity(4)),
                itransform(Matrix::identity(4)) {}

    Sphere(const Material& material) : transform(Matrix::identity(4)),
                                itransform(Matrix::identity(4)),
                                material(material) {}


    bool operator==(const Shape& other) const override {
        const Sphere* otherSphere = dynamic_cast<const Sphere*>(&other);
        if (otherSphere == nullptr) {
            return false;
        }
        bool sameTransform = this->transform == otherSphere->transform;
        bool sameMaterial = this->material == otherSphere->getMaterial();
        return sameTransform && sameMaterial;
    }



    void setTransform(const Matrix& m) override {
        this->transform = m;
        this->itransform = m.inverse();
    }

    void addTransform(const Matrix& m) {
        Matrix newTransform = m * this->transform;
        setTransform(newTransform);
    }

    void resetTransform() {
        setTransform(Matrix::identity(4));
    }

    const Matrix& getTransform() const override {
        return this->transform;
    }

    const Matrix& getInverseTransform() const override {
        return this->itransform;
    }

    /**@brief Computes the normal vector at point p on the unit sphere centered at the origin
     * @param worldPoint
     * @return
     */
    Tuple NormalAt(const Tuple& worldPoint) const override {
        // I have to subtract the sphere's center from p, even though
        // it's the origin because p is a point and not a vector.
        // The difference between two points gives the correct
        // value of w for a vector.

        Tuple objectPoint = this->getInverseTransform() * worldPoint;
        Tuple objectNormal = objectPoint - Tuple::point(0, 0, 0);

        Matrix localToWorld = this->getInverseTransform();
        Tuple worldNormal = localToWorld.transpose() * objectNormal;
        worldNormal.w = 0;
        worldNormal = worldNormal.normalize();

        return worldNormal;

    }

    void setMaterial(const Material& m) override {
        this->material = m;
    }

    const Material& getMaterial() const override {
        return this->material;
    }

    /**@brief Computes the intersections of a ray with this sphere
     * @param ray The ray to intersect with the sphere
     * @param xs The Intersections object to store the results
     */
    void intersect(const Ray& ray, Intersections& xs) const override;

};
