// Intersections.h
// Created by Guglielmo Grillo on 03/01/2026.
// Last modified 13/01/2026.
#pragma once
#include <algorithm>
#include <vector>

#include "linalg/Tuple.h"


// Forward declaration of Shape for the Hit struct
class Shape;

/**@brief Represents an intersection between a ray and a shape
 */
struct Hit {
    double t;                       /// @brief The propagation distance along the ray to the intersection
    const Shape* object = nullptr;  /// @brief Pointer to the intersected shape
    Tuple point;                    /// @brief The point of intersection
    Tuple overPoint;                /// @brief A point slightly above the intersection point to avoid acne. Calculated as point + normal * EPSILON
    Tuple eyev;                     /// @brief Vector pointing from the intersection point to the eye
    Tuple normalv;                  /// @brief The normal vector at the intersection point

    // [TODO] Instead of having a `valid` flag, I could check for !(object == nullptr)
    bool valid;                     /// @brief True if the intersection is valid (i.e., there is an intersection).
    bool inside;                    /// @brief True if the intersection is inside the shape
};

/**@brief Represents a collection of intersections between a ray and shapes
 * @warning [TODO] A proper way to do this would be to use nullptr for the miss hit,
 * but that would require changing a lot of code. For now, I'll use a reference struct.
 */
const Hit missHit = Hit{
    0.0,
    nullptr,
    Tuple::point(0,0,0),
    Tuple::point(0,0,0),
    Tuple::vector(0,0,0),
    Tuple::vector(0,0,0),
    false,
    false
};


class Intersections {
private:
    bool sorted = false;
    std::vector<Hit> hits;

    /**@brief Returns the number of intersections stored
     * @return Number of intersections
     */
    void sort() {
        std::sort(hits.begin(), hits.end(), [](const Hit& a, const Hit& b) {
            return a.t < b.t;
        });
        sorted = true;
    }

    /**@brief Returns the index of the hit intersection (the one with the lowest non-negative t)
     * @return Index of the hit intersection, or -1 if there is no hit
     */
    int GetHitIndex();

public:

    /**@brief Default constructor
     */
    Intersections() {}

    /**@brief Returns the number of intersections stored
     * @return Number of intersections
     */
    int getSize() const {
        return static_cast<int>( hits.size() );
    }

    /**@brief Adds an intersection to the collection
     * @param shape The shape that was intersected
     * @param t The propagation distance along the ray to the intersection
     * @param point The point of intersection
     * @param eyev The vector pointing from the intersection point to the eye
     * @param normalv The normal vector at the intersection point
     */
    void add(const Shape& shape, double t,
             const Tuple& point, const Tuple& eyev, const Tuple& normalv) {

        if(!hits.empty() && t<hits.back().t) {
            sorted = false;
        }

        // Outside of a shape, the normal and the vector to the go in the same half plane
        bool inside = normalv.dot(eyev) < 0;
        Tuple normal = inside ? -normalv : normalv;
        Tuple overPoint = point + normal * EPSILON;

        hits.emplace_back(Hit{
            t,
            &shape,
            point,
            overPoint,
            eyev, normal,
            true,
            inside
        });
    }

    /**@brief Returns the hit intersection (the one with the lowest non-negative t)
     * @return Intersection object representing the hit
     */
    const Hit& GetHit() {
        int idx = GetHitIndex();

        return idx >= 0 ? hits[idx] : missHit;
    }

    const Hit& operator[](int idx) const {
        return hits[idx];
    }



};