//
// Created by Gugli on 10/01/2026.
//
#pragma once
#include <memory>

#include "render/Color.h"
#include "linalg/Tuple.h"
#include "linalg/Matrix.h"

class Pattern {

public:
    virtual ~Pattern () = default;
    virtual std::unique_ptr<Pattern> clone() const = 0;

    virtual Color getColor(Tuple localPoint) const = 0;

    virtual const Matrix& getTransform() const = 0;
    virtual void setTransform(Matrix transform) = 0;

    virtual bool operator==(const Pattern& rhs) const = 0;


};
