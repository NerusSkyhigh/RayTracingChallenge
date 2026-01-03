#include <iostream>

#include <cmath>
#include <numbers>
#include <fstream>

#include "linalg/Tuple.h"
#include "linalg/Matrix.h"
#include "renderer/Canvas.h"
#include "renderer/Ray.h"
#include "shapes/Sphere.h"
#include "shapes/Hit.h"

int main() {

    // Ch 4: Draw a clock face with dots at each hour position
    Canvas c(100, 100);
    Tuple dot = Tuple::point(20, 0, 0);
    Matrix rotation = Matrix::rotationZ(2*std::numbers::pi/12); // 45 degrees


    for (int x = 0; x < 12; x++) {
        dot = rotation*dot;
        int canvasX = static_cast<int>(std::round((dot.x) + c.width / 2));
        int canvasY = static_cast<int>(std::round((dot.y) + c.height / 2));
        c.writePixel(canvasX, canvasY, Color(1, 1, 1));
    }

    c.ToPPMFile("../cp4_clock.ppm");
    return 0;
}