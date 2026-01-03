// Canvas.test.cpp
// Created by Guglielmo Grillo on 30/12/2025.
//
#include <string>

#include "catch2/catch_test_macros.hpp"

#include "renderer/Canvas.h"
#include "renderer/Color.h"


TEST_CASE("The canvas is made of pixels") {
    Canvas c(10, 20);
    REQUIRE(c.width == 10);
    REQUIRE(c.height == 20);
    for (int y = 0; y < c.height; y++) {
        for (int x = 0; x < c.width; x++) {
            REQUIRE(c.pixelAt(x, y) == Color(0, 0, 0));
        }
    }
}

TEST_CASE("Write and Read a pixel") {
    Canvas c(10, 20);
    Color red(1, 0, 0);
    c.writePixel(2, 3, red);
    REQUIRE(c.pixelAt(2, 3) == red);
}

TEST_CASE("Constructing the PPM header") {
    Canvas c(5, 3);
    std::string ppm = c.ToPPMString();
    std::string expectedHeader =
        "P3\n"
        "5 3\n"
        "255\n";
    REQUIRE(ppm.substr(0, expectedHeader.length()) == expectedHeader);
}

TEST_CASE("Constructing the PPM pixel data") {
    Canvas c(5, 3);
    Color c1(1.5, 0, 0);
    Color c2(0, 0.5, 0);
    Color c3(-0.5, 0, 1);
    c.writePixel(0, 0, c1);
    c.writePixel(2, 1, c2);
    c.writePixel(4, 2, c3);
    std::string ppm = c.ToPPMString();
    std::string expectedPixels =
        "P3\n"
        "5 3\n"
        "255\n"
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
    REQUIRE(ppm == expectedPixels);
}

TEST_CASE("Splitting long lines in PPM files") {
    Canvas c(10, 2);
    Color color(1, 0.8, 0.6);
    for (int y = 0; y < c.height; y++) {
        for (int x = 0; x < c.width; x++) {
            c.writePixel(x, y, color);
        }
    }
    std::string ppm = c.ToPPMString();
    std::string expectedPixels =
        "P3\n"
        "10 2\n"
        "255\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
    REQUIRE(ppm == expectedPixels);
}