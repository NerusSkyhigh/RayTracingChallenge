//
// Created by Gugli on 04/01/2026.
//

#include <iostream>

#include <cmath>
#include <numbers>
#include <fstream>

#include "linalg/Tuple.h"
#include "linalg/Matrix.h"
#include "render/Canvas.h"
#include "../src/geometry/Ray.h"
#include "../src/render/material/Material.h"
#include "../src/scene/PointLight.h"
#include "../src/geometry/Sphere.h"


Tuple CanvasPixelToWorld(int x, int y, Canvas canvas, Tuple canvasCenter, double pixelSize) {

    // Compute the origin of the canvas in world space
    // origin = top left corner; x increases to the right, y increases downwards
    double canvasWorldOriginX = canvasCenter.x - (canvas.width / 2.0) * pixelSize;
    double canvasWorldOriginY = canvasCenter.y + (canvas.height / 2.0) * pixelSize;

    // Compute the world coordinates of the pixel (x, y)
    // The +0.5 is to get the center of the pixel
    double WorldX = canvasWorldOriginX + (x+0.5) * pixelSize;
    double WorldY = canvasWorldOriginY - (y+0.5) * pixelSize;

    return Tuple::point(WorldX, WorldY, canvasCenter.z);
}

Tuple CanvasWorldToPixel(Tuple worldPos, Canvas canvas, Tuple canvasCenter, double pixelSize) {
    double canvasWorldOriginX = canvasCenter.x - (canvas.width / 2.0) * pixelSize;
    double canvasWorldOriginY = canvasCenter.y + (canvas.height / 2.0) * pixelSize;

    double x = (worldPos.x - canvasWorldOriginX) / pixelSize - 0.5;
    double y = (canvasWorldOriginY - worldPos.y) / pixelSize - 0.5;

    //assert(y >= 0 && y < canvas.height);
    //assert(x >= 0 && x < canvas.width);

    return Tuple::point(x, y, canvasCenter.z);
}


int main() {
    // Set up the canvas as a rectangle parallel to the xy plane
    // at z = 10, width = 7 [world units], height = 7 [world units]
    Tuple canvasCenter = Tuple::point(0, 0, 10);
    double canvasSide = 7.0;
    double resolution = 128*128;
    double pixelSize = canvasSide / std::sqrt(resolution);

    Canvas canvas(sqrt(resolution), sqrt(resolution) );

    // Prepare the sphere to be drawn
    Material material;
    material.color = Color(1, 0.2, 1);
    Sphere sphere(material);
    sphere.addTransform(Matrix::scaling(1, 1, 1));

    // Add a light
    PointLight light(Tuple::point(-10, 10, -10), Color(1, 1, 1));

    // Prepare the origin of the observer; direction will change based on the pixel being rendered
    Tuple observer = Tuple::point(0, 0, -5);

    for (int y = 0; y < canvas.height; y++) {
        for (int x = 0; x < canvas.width; x++) {

            Tuple pixelWorldPos = CanvasPixelToWorld(x, y, canvas, canvasCenter, pixelSize);
            Tuple direction = (pixelWorldPos - observer).normalize();
            Ray ray(observer, direction);

            Intersections xs;
            //Intersections xs = ray.transform(sphere.GetInverseTransform()).intersect(sphere);
            sphere.intersect(ray, xs);
            Hit worldHit = xs.GetHit();

            if (worldHit.valid) {
                Color c = material.lighting(light, worldHit.point, -ray.direction, sphere.NormalAt(worldHit.point));
                Tuple canvasHitPoint = CanvasWorldToPixel(worldHit.point, canvas, canvasCenter, pixelSize);
                int X = static_cast<int>(canvasHitPoint.x);
                int Y = static_cast<int>(canvasHitPoint.y);
                canvas.writePixel(X, Y, c);
            }
        }
    }
    canvas.ToPPMFile("../cp6_LightingSphere.ppm");


    return 0;
}