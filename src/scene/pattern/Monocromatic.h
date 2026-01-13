//
// Created by Gugli on 12/01/2026.
//
#pragma once

#include "scene/pattern/Pattern.h"
#include "render/Color.h"

class Monocromatic : public Pattern {
private:
    Color color;

public:
    Monocromatic(Color color) : color(color) {}

    std::unique_ptr<Pattern> clone() const override {
        return std::make_unique<Monocromatic>(*this);
    }

    Color getColor(Tuple localPoint) const override {
        return color;
    }

    void setTransform(Matrix transform) override {
        // A monochromatic pattern has no color
    };

    bool operator==(const Pattern& rhs) const override {
        auto o = dynamic_cast<const Monocromatic*>(&rhs);
        return o && color == o->color;
    }
};
