//
// Created by Gugli on 14/01/2026.
//

#pragma once

#include "Pattern.h"
#include "scene/pattern/Monocromatic.h"
#include "render/Color.h"


class CheckerPattern : public Pattern {
private:
    std::unique_ptr<Pattern> a;
    std::unique_ptr<Pattern> b;
    Matrix transform;
    Matrix itransform;

public:
    CheckerPattern() : a( std::make_unique<Monocromatic>(Color::White())),
                        b( std::make_unique<Monocromatic>(Color::Black()) ),
                        transform(Matrix::identity(4)),
                        itransform(Matrix::identity(4)) {}

    CheckerPattern(const Color& ca, const Color& cb) :  a( std::make_unique<Monocromatic>(ca) ),
                                                        b( std::make_unique<Monocromatic>(cb) ),
                                                        transform(Matrix::identity(4)),
                                                        itransform(Matrix::identity(4)) {}

    CheckerPattern(std::unique_ptr<Pattern> a, std::unique_ptr<Pattern> b) :    a( std::move(a) ),
                                                                                b( std::move(b) ),
                                                                                transform(Matrix::identity(4)),
                                                                                itransform(Matrix::identity(4)){}

    std::unique_ptr<Pattern> clone() const override {
        auto p = std::make_unique<CheckerPattern>(
            a->clone(),
            b->clone()
        );
        p->setTransform(transform);
        return p;
    }

    Color getColor(Tuple localPoint) const override {
        // Convert the point to pattern space
        Tuple patternPoint = itransform * localPoint;

        int xi = static_cast<int>(std::floor( patternPoint.x ));
        int yi = static_cast<int>(std::floor( patternPoint.y ));
        int zi = static_cast<int>(std::floor( patternPoint.z ));

        return (xi+yi+zi) % 2 == 0 ? a->getColor(patternPoint) : b->getColor(patternPoint);
    }

    virtual void setTransform(Matrix transform) {
        this->transform = transform;
        this->itransform = transform.inverse();
    }

    const Matrix& getTransform() const override {
        return transform;
    }

    virtual bool operator==(const Pattern& rhs) const {
        auto other = dynamic_cast<const CheckerPattern*>(&rhs);
        if (!other) {
            return false;
        }
        bool samePatternA = *a == *other->a;
        bool samePatternB = *b == *other->b;
        bool sameTransform = transform == other->transform;

        return samePatternA && samePatternB && sameTransform;
    }
};