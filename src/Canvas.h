//
// Created by Gugli on 30/12/2025.
//
#pragma once

#include <vector>
#include <string>

#include "Color.h"

class Canvas {
public:
    const int width;
    const int height;

    std::vector<Color> pixels;

    Canvas(const int width, const int height) : width(width), height(height) {
        pixels = std::vector<Color>(width * height, Color(0, 0, 0));
    }

    void writePixel(const int x, const int y, const Color &color) {
        pixels[y * width + x] = color;
    }

    Color pixelAt(const int x, const int y) const {
        return pixels[y * width + x];
    }

    // [TODO] Save to file
    static std::string canvasToPPM(const Canvas &canvas);
};
