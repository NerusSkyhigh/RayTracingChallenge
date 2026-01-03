// tuple.h
// Created by Guglielmo Grillo on 30/12/2025.
//

#include "Tuple.h"

Tuple Tuple::point(const double x, const double y, const double z) {
    return Tuple{x, y, z, 1.};
}

Tuple Tuple::vector(const double x, const double y, const double z) {
    return Tuple{x, y, z, 0.};
}
