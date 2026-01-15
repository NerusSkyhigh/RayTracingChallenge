//
// Created by Gugli on 04/01/2026.
//

#pragma once

#include <memory>

#include "render/Color.h"
#include "scene/light/PointLight.h"
#include "scene/pattern/Pattern.h"
#include "scene/pattern/Monocromatic.h"


class Material {
private:
    double ambient; /// Ambient coefficient; this is assumed to be uniform across the surface
    double diffuse;
    double specular;
    double shininess;
    std::unique_ptr<Pattern> pattern;

public:
    Material(const Material& other) :   ambient(other.ambient),
                                        diffuse(other.diffuse),
                                        specular(other.specular),
                                        shininess(other.shininess),
                                        pattern(other.pattern ? other.pattern->clone() : nullptr)
                                        {}

    Material() :    ambient(0.1),
                    diffuse(0.9),
                    specular(0.9),
                    shininess(200.0),
                    pattern(std::make_unique<Monocromatic>(Color::White())) {}

    Material(const Color& color, double ambient, double diffuse, double specular, double shininess) :
                    ambient(ambient),
                    diffuse(diffuse),
                    specular(specular),
                    shininess(shininess),
                    pattern(std::make_unique<Monocromatic>(color)) {}


    Material& operator=(const Material& other) {
        if (this == &other) return *this;
        ambient   = other.getAmbient();
        diffuse   = other.getDiffuse();
        specular  = other.getSpecular();
        shininess = other.getShininess();
        pattern   = other.getPattern().clone();
        return *this;
    }

    void setAmbient(double a) { ambient = a; }
    double getAmbient() const { return ambient; }

    void setDiffuse(double d) { diffuse = d; }
    double getDiffuse() const { return diffuse; }

    void setSpecular(double s) { specular = s; }
    double getSpecular() const { return specular; }

    void setShininess(double sh) { shininess = sh; }
    double getShininess() const { return shininess; }

    void setColor(const Color& color) { pattern = std::make_unique<Monocromatic>(color); }
    Color getColor(const Tuple& localPoint) const { return pattern->getColor(localPoint); }

    void setPattern(std::unique_ptr<Pattern> p) { pattern = std::move(p); }
    const Pattern& getPattern() const { return *pattern; }

    bool operator==(const Material& m) const {
        bool samePattern = (*this->pattern) == (*m.pattern);
        bool sameAmbient = APPROX_EQUAL(this->ambient, m.ambient);
        bool sameDiffuse = APPROX_EQUAL(this->diffuse, m.diffuse);
        bool sameSpecular = APPROX_EQUAL(this->specular, m.specular);
        bool sameShininess = APPROX_EQUAL(this->shininess, m.shininess);
        return samePattern && sameAmbient && sameDiffuse && sameSpecular && sameShininess;
    }

    Color lighting(const PointLight& light, const Tuple& position, const Tuple& eyev, const Tuple& normalv, bool inShadow) const {

        // Combine the surface color with the light's color/intensity
        Color effectiveColor = this->getColor(position).hadamard(light.intensity);

        // Ambient component (assumed to be uniform across the surface)
        Color ambientComponent = effectiveColor * this->ambient;

        if (inShadow) {
            return ambientComponent;
        }

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
