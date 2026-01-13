//
// Created by Gugli on 04/01/2026.
//
#include "Intersections.h"

/**@brief Returns the index of the hit intersection (the one with the lowest non-negative t)
 * @return Index of the hit intersection, or -1 if there is no hit
 */
int Intersections::GetHitIndex() {

    if(!sorted) {
        sort();
    }


    // ChatGPT suggest to use a linear search here since
    // the number of intersections is usually small. I'll
    // keep the bisection code commented for future reference.
    int idx = -1;
    for (const auto& h : hits) {
        idx++;
        if (h.t > 0) return idx;
    }
    return -1;

    /*
    // Find the lowest non-negative t using bisection
    int minIdx = 0;
    int maxIdx = getSize() - 1;

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
    */
}