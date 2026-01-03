#include <iostream>

#include <cmath>
#include <numbers>
#include <fstream>

#include "Canvas.h"
#include "Tuple.h"
#include "Matrix.h"
#include "Ray.h"
#include "Sphere.h"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
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


    // Ch 5: Sphere
    Canvas c5(100, 100);
    Sphere sphere{};
    sphere.addTransform(Matrix::scaling(45, 45, 45));
    sphere.addTransform(Matrix::translation(c5.width/2, c5.height/2, 0));

    for (int y = 0; y < c5.height; y++) {
        for (int x = 0; x < c5.width; x++) {
            Tuple origin = Tuple::point(x, y, -50);
            Tuple direction = Tuple::vector(0, 0, 1);

            Ray ray(origin, direction);

            Intersections intersections = ray.transform(sphere.transform.inverse()).intersect(sphere);
            if (intersections.size > 0) {
                Intersections hit = Intersections::hit(intersections);
                double t = hit.solutions[0];
                Tuple point = ray.origin + ray.direction * t;
                c5.writePixel(point.x, point.y, Color(1, 1, 1));
                printf("Intersection at t=%.2f at point (%.2f, %.2f, %.2f)\n", t, point.x, point.y, point.z);
            }
        }
    }
    c5.ToPPMFile("../cp5_sphere.ppm");


    return 0;
}