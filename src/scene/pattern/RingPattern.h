//
// Created by Gugli on 14/01/2026.
//

#pragma once

#include "Pattern.h"
#include "render/Color.h"


class RingPattern : public Pattern {
private:
    Color colorA;
    Color colorB;
    Matrix transform;
    Matrix itransform;

public:
    RingPattern(const Color& a, const Color& b) : colorA(a),
                                                  colorB(b),
                                                  transform(Matrix::identity(4)),
                                                  itransform(Matrix::identity(4)){}

    std::unique_ptr<Pattern> clone() const override {
        return std::make_unique<RingPattern>(*this);
    }

    Color getColor(Tuple localPoint) const override {
        // Convert the point to pattern space
        Tuple patternPoint = itransform * localPoint;

        double rxy = sqrt( patternPoint.x * patternPoint.x + patternPoint.z * patternPoint.z );

        int var = static_cast<int>(std::floor( rxy ));
        return var % 2 == 0 ? colorA : colorB;
    }

    virtual void setTransform(Matrix transform) {
        this->transform = transform;
        this->itransform = transform.inverse();
    }

    const Matrix& getTransform() const override {
        return transform;
    }

    virtual bool operator==(const Pattern& rhs) const {
        auto other = dynamic_cast<const RingPattern*>(&rhs);
        if (other) {
            return false;
        }
        bool sameColorA = colorA == other->colorA;
        bool sameColorB = colorB == other->colorB;
        bool sameTransform = transform == other->transform;

        return sameColorA && sameColorB && sameTransform;
    }
};