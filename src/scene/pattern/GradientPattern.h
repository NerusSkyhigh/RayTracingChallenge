//
// Created by Gugli on 14/01/2026.
//
#pragma once

#include "Pattern.h"
#include "render/Color.h"
#include "linalg/Matrix.h"
#include "linalg/Tuple.h"


class GradientPattern : public Pattern {
private:
    Color start;
    Color end;
    Matrix transform;
    Matrix itransform;

public:
    GradientPattern() : start(Color::White()),
                        end(Color::Black()),
                        transform(Matrix::identity(4)),
                        itransform(Matrix::identity(4)) {}

    GradientPattern(Color start, Color end, Matrix transform) : start(start),
                                                                end(end),
                                                                transform(transform),
                                                                itransform(transform.inverse()) {}


    std::unique_ptr<Pattern> clone() const override {
        return std::make_unique<GradientPattern>(*this);
    }


    Color getColor(Tuple localPoint) const override {
        // Convert the point to pattern space
        Tuple patternPoint = itransform * localPoint;

        return LERP(start, end, patternPoint.x);
    }

    virtual void setTransform(Matrix transform) {
        this->transform = transform;
        this->itransform = transform.inverse();
    }

    const Matrix& getTransform() const override {
        return transform;
    }

    bool operator==(const Pattern& rhs) const {
        auto other = dynamic_cast<const GradientPattern*>(&rhs);
        if (other) {
            return false;
        }
        bool sameStart = start == other->start;
        bool sameEnd = end == other->end;
        bool sameTransform = transform == other->transform;

        return sameStart && sameEnd && sameTransform;
    }

};

