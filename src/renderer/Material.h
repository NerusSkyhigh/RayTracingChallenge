//
// Created by Gugli on 04/01/2026.
//

#pragma once

#include "Color.h"
#include "PointLight.h"


class Material {
public:
    Color color;
    double ambient; /// Ambient coefficient; this is assumed to be uniform across the surface
    double diffuse;
    double specular;
    double shininess;


    Material() : color(Color::White()),
                    ambient(0.1),
                    diffuse(0.9),
                    specular(0.9),
                    shininess(200.0) {}

    Material(const Color& color, double ambient, double diffuse, double specular, double shininess)
        : color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

    bool operator==(const Material& m) const {
        bool sameColor = this->color == m.color;
        bool sameAmbient = APPROX_EQUAL(this->ambient, m.ambient);
        bool sameDiffuse = APPROX_EQUAL(this->diffuse, m.diffuse);
        bool sameSpecular = APPROX_EQUAL(this->specular, m.specular);
        bool sameShininess = APPROX_EQUAL(this->shininess, m.shininess);
        return sameColor && sameAmbient && sameDiffuse && sameSpecular && sameShininess;
    }

    Color lighting(const PointLight& light, const Tuple& position, const Tuple& eyev, const Tuple& normalv) const {

        // Combine the surface color with the light's color/intensity
        Color effectiveColor = this->color.hadamard(light.intensity);

        // Ambient component (assumed to be uniform across the surface)
        Color ambientComponent = effectiveColor * this->ambient;

        // Direction to the light source
        Tuple lightv = (light.position - position).normalize();

        // Cosine of the angle between the light vector and the normal vector
        double lightDotNormal = lightv.dot(normalv);

        // Initialize diffuse and specular components to black
        // They will remain black if the light is on the other side of the surface (lightDotNormal <= 0)
        Color diffuseComponent  = Color::Black();
        Color specularComponent = Color::Black();

        if (lightDotNormal > 0) {
            diffuseComponent = effectiveColor * this->diffuse * lightDotNormal;

            // Light reflected from the object around the normal
            Tuple reflectv = (-lightv).reflect(normalv);

            // Cosine of the angle between the reflection vector and the eye vector
            double reflecDotEye = reflectv.dot(eyev);

            if (reflecDotEye > 0) {
                double factor = std::pow(reflecDotEye, this->shininess);
                specularComponent = light.intensity * this->specular * factor;
            }
        }

        return ambientComponent + diffuseComponent + specularComponent;
    }


};
