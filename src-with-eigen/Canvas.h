//
// Created by Gugli on 30/12/2025.
//
#pragma once

#include <string>

#include <Eigen/Dense>

#include "../src/renderer/Color.h"

class Canvas {
public:
    const int width;
    const int height;

    // Pixels are stored in a eigen matrix
    Eigen::Matrix<Color, Eigen::Dynamic, Eigen::Dynamic> pixels;

    Canvas(const int width, const int height) : width(width), height(height) {
        pixels = Eigen::Matrix<Color, Eigen::Dynamic, Eigen::Dynamic>(height, width);
    }

    void writePixel(const int x, const int y, const Color &color) {
        pixels(y, x) = color;
    }

    Color pixelAt(const int x, const int y) const {
        return pixels(y, x);
    }

    // [TODO] Save to file
    static std::string ToPPMString(const Canvas &canvas);
};
