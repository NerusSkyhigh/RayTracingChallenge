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
        Color effectiveColor = this->color.hadamard(light.intensity);

        // Direction to the light source
        Tuple lightv = (light.position - position).normalize();
        Color ambientComponent = effectiveColor * this->ambient;

        // Cosine of the angle between the light vector and the normal vector
        double cosLv = lightv.dot(normalv);
        Color diffuseComponent = Color::Black();
        Color specularComponent = Color::Black();

        if (cosLv > 0) {
            diffuseComponent = effectiveColor * this->diffuse * cosLv;

            Tuple reflectv = (-lightv).reflect(normalv);

            // Cosine of the angle between the reflection vector and the eye vector
            double cosRE = reflectv.dot(eyev);

            if (cosRE <= 0) {
                specularComponent = Color(0, 0, 0);
            } else {
                double factor = std::pow(cosRE, this->shininess);
                specularComponent = light.intensity * this->specular * factor;
            }
        }

        return ambientComponent + diffuseComponent + specularComponent;
    }


};
