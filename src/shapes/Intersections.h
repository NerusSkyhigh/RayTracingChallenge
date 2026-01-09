//
// Created by Gugli on 03/01/2026.
//
#pragma once
#include <algorithm>
#include <memory>
#include <vector>

#include "linalg/Tuple.h"


// Forward declaration of Shape for the Hit struct
class Shape;
struct Hit {
    double t;
    const Shape* object;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    bool valid;
    bool inside; // True if inside and the normal is inverted
};


class Intersections {
private:
    bool sorted = false;
    int hitIndex;
    std::vector<Hit> hits;

public:
    int size;

    Intersections() : size(0) {}

    void add(const Shape& shape, double t,
             const Tuple& point, const Tuple& eyev, const Tuple& normalv) {

        if(!hits.empty() && t<hits.back().t) {
            sorted = false;
        }

        // Outside of a shape, the normal and the vector to the go in the same half plane
        bool inside = normalv.dot(eyev) < 0;
        Tuple normal = inside ? -normalv : normalv;

        hits.emplace_back(Hit{t, &shape, point, eyev, normal, true, inside});
        size++;
    }

    /**@brief Sorts the intersections in ascending order of t
     */
    void sort() {
        std::sort(hits.begin(), hits.end(), [](const Hit& a, const Hit& b) {
            return a.t < b.t;
        });
        sorted = true;
    }

    int GetHitIndex() {
        if(hits.empty()) {
            return -1;
        }

        if(!sorted) {
            sort();
        }

        // Find the lowest non-negative t using bisection
        int minIdx = 0;
        int maxIdx = size - 1;

        while (minIdx < maxIdx) {
            int midIdx = (minIdx + maxIdx) / 2;

            if (hits[midIdx].t <= 0) { // Zero is not considered a hit
                minIdx = midIdx + 1;
            } else {
                maxIdx = midIdx;
            }
        }

        if (hits[minIdx].t <= 0) {
            return -1; // No non-negative intersections
        }

        return minIdx;
    }

    /**@brief Returns the hit intersection (the one with the lowest non-negative t)
     * @return Intersection object representing the hit
     */
    Hit GetHit() {
        int hitIdx = GetHitIndex();

        if (hitIdx >= 0 && hitIdx < size) {
            return hits[hitIdx];
        } else {
            // Return an invalid intersection if no hit is found
            Tuple o = Tuple::point(0,0,0);
            return Hit(0, nullptr, o, o, o, false);
        }
    }

    Hit operator[](int index) const {
        assert(index >= 0 && index < size);
        return hits[index];
    }



};