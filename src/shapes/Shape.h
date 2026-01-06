//
// Created by Gugli on 03/01/2026.
//
#pragma once

#include "linalg/Matrix.h"
#include "renderer/Material.h"


class Shape {

public:

    virtual ~Shape() = default;

    virtual Matrix GetTransform() const = 0;

    /** @brief Returns the inverse of the transformation matrix
     * @note It is highly recommended to cache this value if used multiple times
     * @return Inverse of the transformation matrix
     */
    virtual Matrix GetInverseTransform() const = 0;

    virtual Material GetMaterial() const = 0;
};