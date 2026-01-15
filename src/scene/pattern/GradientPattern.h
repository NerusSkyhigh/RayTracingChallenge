//
// Created by Gugli on 14/01/2026.
//
#pragma once

#include "Pattern.h"
#include "scene/pattern/Monocromatic.h"
#include "render/Color.h"
#include "linalg/Matrix.h"
#include "linalg/Tuple.h"


class GradientPattern : public Pattern {
private:
    std::unique_ptr<Pattern> start;
    std::unique_ptr<Pattern> end;
    Matrix transform;
    Matrix itransform;

public:
    GradientPattern() : start( std::make_unique<Monocromatic>(Color::White())),
                        end( std::make_unique<Monocromatic>(Color::Black()) ),
                        transform(Matrix::identity(4)),
                        itransform(Matrix::identity(4)) {}

    GradientPattern(Color start, Color end) : start( std::make_unique<Monocromatic>(start) ),
                                                                end( std::make_unique<Monocromatic>(end) ),
                                                                transform(Matrix::identity(4)),
                                                                itransform(Matrix::identity(4)) {}
    GradientPattern(std::unique_ptr<Pattern> start, std::unique_ptr<Pattern> end) : start( std::move(start) ),
                                                                                    end( std::move(end) ),
                                                                                    transform(Matrix::identity(4)),
                                                                                    itransform(Matrix::identity(4)){}

    std::unique_ptr<Pattern> clone() const override {
        auto p = std::make_unique<GradientPattern>(
            start->clone(),
            end->clone()
        );
        p->setTransform(transform);
        return p;
    }


    Color getColor(Tuple localPoint) const override {
        // Convert the point to pattern space
        Tuple patternPoint = itransform * localPoint;

        double t = patternPoint.x - std::floor(patternPoint.x);
        return LERP(start->getColor(patternPoint),
                end->getColor(patternPoint), t);
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
        if (!other) {
            return false;
        }
        bool sameStart = *start == *other->start;
        bool sameEnd = *end == *other->end;
        bool sameTransform = transform == other->transform;

        return sameStart && sameEnd && sameTransform;
    }

};

