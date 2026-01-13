//
// Created by Gugli on 03/01/2026.
//
#pragma once

#include "linalg/Matrix.h"
#include "scene/material//Material.h"
#include "Ray.h"
#include "Intersections.h"


class Shape {

public:
    virtual ~Shape() = default;

    // ---- TRANSFORMATIONS ---- //
    /** @brief Sets the transformation matrix for the shape
     * @param m Transformation matrix
     */
    virtual void setTransform(const Matrix& m) = 0;

    /** @brief Returns the transformation matrix for the shape
     * @return Transformation matrix
     */
    virtual const Matrix& getTransform() const = 0;

    /** @brief Returns the inverse of the transformation matrix
     * @note It is highly recommended to cache this value if used multiple times
     * @return Inverse of the transformation matrix
     */
    virtual const Matrix& getInverseTransform() const = 0;

    // ---- MATERIALS ---- //
    /** @brief Sets the material for the shape
     * @param material Material to set
     */
    virtual void setMaterial(const Material& material) = 0;

    /** @brief Returns the material of the shape
     * @return Material of the shape
     */
    virtual const Material& getMaterial() const = 0;


    virtual Tuple NormalAt(const Tuple& worldPoint) const = 0;

    virtual void intersect(const Ray& ray, Intersections& xs) const = 0;

    virtual bool operator==(const Shape&) const = 0;
};
