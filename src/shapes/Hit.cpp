//
// Created by Gugli on 03/01/2026.
//

#include "Hit.h"

Hit Hit::find(const Intersections& intersections, const Ray ray)  {

    double minT = std::numeric_limits<double>::infinity();
    for (double t : intersections.solutions) {
        if (t >= 0 && t < minT) {
            minT = t;
        }
    }
    if (minT == std::numeric_limits<double>::infinity()) {
        return Hit(*intersections.shape);
    } else {
        Tuple point = ray.origin + ray.direction * minT;
        return Hit{minT, *intersections.shape, point};
    }
}