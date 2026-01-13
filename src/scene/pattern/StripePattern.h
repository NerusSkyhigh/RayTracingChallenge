//
// Created by Gugli on 10/01/2026.
//

#pragma once

#include "Pattern.h"
#include "render/Color.h"


class StripePattern : public Pattern {
private:
    Color colorA;
    Color colorB;
    Matrix transform;
    Matrix itransform;

public:
    StripePattern(const Color& a, const Color& b)
        : colorA(a), colorB(b) {}

    std::unique_ptr<Pattern> clone() const override {
        return std::make_unique<StripePattern>(*this);
    }

    Color getColor(Tuple localPoint) const override {

        int var = static_cast<int>(std::floor(localPoint.x));
        return var % 2 == 0 ? colorA : colorB;
    }

    virtual void setTransform(Matrix transform) {
        this->transform = transform;
        this->itransform = transform;
    }

    virtual bool operator==(const Pattern& rhs) const {
        auto other = dynamic_cast<const StripePattern*>(&rhs);
        if (other) {
            return false;
        }
        bool sameColorA = colorA == other->colorA;
        bool sameColorB = colorB == other->colorB;
        bool sameTransform = transform == other->transform;

        return sameColorA && sameColorB && sameTransform;
    }
};