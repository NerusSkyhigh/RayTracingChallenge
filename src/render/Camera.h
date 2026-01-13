// Camera.h
// Created by Gugli on 07/01/2026.
//
#pragma once

#include "linalg/Matrix.h"
#include "linalg/ViewTransform.h"
#include "../geometry/Ray.h"
#include "Canvas.h"

class Camera {
private:
    Matrix transform;
    Matrix itransform;

public:
    int hsize; // horizontal size in pixels
    int vsize; // vertical size in pixels
    double fieldOfView; // in radians

    double halfWidth;
    double halfHeight;
    double pixelSize;

    Camera(int hsize, int vsize, double fieldOfView) : hsize(hsize),
                                                       vsize(vsize),
                                                       fieldOfView(fieldOfView),
                                                       transform(Matrix::identity(4)),
                                                       itransform(Matrix::identity(4))
    {

        // Assume the canvas is 1 unit away from the camera
        double halfView = tan(fieldOfView / 2.0);
        double aspect = static_cast<double>(hsize) / static_cast<double>(vsize);

        if (aspect >= 1.0) {
            this->halfWidth = halfView;
            this->halfHeight = halfView / aspect;
        } else {
            this->halfWidth = halfView * aspect;
            this->halfHeight = halfView;
        }
        this->pixelSize = (this->halfWidth * 2.0) / static_cast<double>(hsize);
    }

    void SetViewTransform(const ViewTransform& vt) {
        this->transform = vt.GetTransform();
        this->itransform = vt.GetInverseTransform();
    }

    /**@brief Sets the transformation matrix for the camera
     *
     * @param m
     * @return
     * @warning This will overwrite any previous view transformation set with SetViewTransform
     */
    void SetTransform(const Matrix& m) {
        this->transform = m;
        this->itransform = m.inverse();
    }

    Matrix GetTransform() const {
        return transform;
    }

    Matrix GetInverseTransform() const {
        return itransform;
    }



    Ray rayForPixel(int px, int py) const {
        // Offset from the edge of the canvas to the pixel's center
        double xOffset = (px + 0.5) * this->pixelSize;
        double yOffset = (py + 0.5) * this->pixelSize;

        // World coordinates of the pixel
        double worldX = this->halfWidth - xOffset;
        double worldY = this->halfHeight - yOffset;

        // Using the camera matrix, transform the canvas point and the origin
        // then compute the ray's direction vector
        Tuple pixel  = this->GetInverseTransform() * Tuple::point(worldX, worldY, -1);
        Tuple origin = this->GetInverseTransform() * Tuple::point(0, 0, 0);
        Tuple direction = (pixel - origin).normalize();

        return Ray(origin, direction);
    }

    Canvas render(const class World& world) const {
        Canvas canvas(this->hsize, this->vsize);

        for (int y = 0; y < this->vsize; ++y) {
            for (int x = 0; x < this->hsize; ++x) {
                Ray ray = this->rayForPixel(x, y);
                Color color = world.colorAt(ray);
                canvas.writePixel(x, y, color);
            }
        }

        return canvas;
    }

};

