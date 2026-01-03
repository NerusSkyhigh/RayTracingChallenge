//
// Created by Gugli on 03/01/2026.
//
#pragma once

#include <vector>
#include "Shape.h"

class Intersections {

public:
    int size;

    // [TODO] Store intersections in order of t so it is faster to find the hit
    // [TODO] Maybe even have two separate vectors for negative and positive t values
    std::vector<double> solutions;
    const Shape* shape;


    Intersections(const Shape& shape) : size(0), solutions(), shape(&shape) {}

    void addSolution(const double t) {
        solutions.push_back(t);
        size++;
    }
};