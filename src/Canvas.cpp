//
// Created by Gugli on 30/12/2025.
//
#include <string>
#include <algorithm>

#include "Canvas.h"




std::string Canvas::canvasToPPM(const Canvas& canvas) {
    std::string ppm;
    ppm += "P3\n";
    ppm += std::to_string(canvas.width) + " " + std::to_string(canvas.height) + "\n";
    ppm += "255\n";

    for (int y = 0; y < canvas.height; y++) {
        std::string line;
        for (int x = 0; x < canvas.width; x++) {
            Color pixel = canvas.pixelAt(x, y);

            // Clamp the color values to [0, 1] and scale to [0, 255]
            int r = static_cast<int>(std::round(std::clamp(pixel.r, 0.0, 1.0) * 255));
            int g = static_cast<int>(std::round(std::clamp(pixel.g, 0.0, 1.0) * 255));
            int b = static_cast<int>(std::round(std::clamp(pixel.b, 0.0, 1.0) * 255));

            // rgb components as strings
            std::string components[] = {
                std::to_string(r),
                std::to_string(g),
                std::to_string(b)
            };

            for (const auto& comp : components) {
                // Check if adding this component would exceed 70 characters
                if (line.length() + comp.length() + 1 > 70) {
                    // If the is too long, flush the line to ppm and start a new line
                    ppm += line + "\n";
                    line = comp;
                } else {
                    if (!line.empty()) {
                        line += " ";
                    }
                    line += comp;
                }
            }
        }
        if (!line.empty()) {
            ppm += line + "\n";
        }
    }

    return ppm;
}
