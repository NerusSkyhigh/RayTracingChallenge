//
// Created by Gugli on 03/01/2026.
//
#pragma once

#include "linalg/Matrix.h"
#include "renderer/Material.h"
#include "renderer/Ray.h"
#include "shapes/Intersections.h"


class Shape {

public:
    Material material;

    virtual ~Shape() = default;

    virtual void SetTransform(const Matrix& m) = 0;
    virtual Matrix GetTransform() const = 0;

    /** @brief Returns the inverse of the transformation matrix
     * @note It is highly recommended to cache this value if used multiple times
     * @return Inverse of the transformation matrix
     */
    virtual Matrix GetInverseTransform() const = 0;

    virtual void SetMaterial(const Material& material) = 0;
    virtual Material GetMaterial() const = 0;

    virtual void intersect(const Ray& ray, Intersections& xs) const = 0;
};
