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
    // Ch 5: Sphere
    Canvas c(100, 100);
    Sphere sphere{};
    sphere.addTransform(Matrix::scaling(45, 45, 45));
    sphere.addTransform(Matrix::translation(c.width/2, c.height/2, 0));

    for (int y = 0; y < c.height; y++) {
        for (int x = 0; x < c.width; x++) {
            Tuple origin = Tuple::point(x, y, -50);
            Tuple direction = Tuple::vector(0, 0, 1);

            Ray ray(origin, direction);
            Intersections intersections = ray.transform(sphere.transform.inverse()).intersect(sphere);
            Hit hit = Hit::find(intersections, ray);

            if (hit.isValid()) {
                int X = static_cast<int>(std::round(hit.point.x));
                int Y = static_cast<int>(std::round(hit.point.y));
                c.writePixel(X, Y, Color(1, 1, 1));
            }
        }
    }
    c.ToPPMFile("../cp5_sphere.ppm");


    return 0;
}