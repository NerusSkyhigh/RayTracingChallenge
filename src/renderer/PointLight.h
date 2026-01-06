//
// Created by Gugli on 04/01/2026.
//

#pragma once

#include "linalg/Tuple.h"
#include "renderer/Color.h"

class PointLight {
public:
    Tuple position;
    Color intensity;

    PointLight(const Tuple &position, const Color &intensity) : position(position), intensity(intensity) {}
};