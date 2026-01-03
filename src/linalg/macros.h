#pragma once

#ifndef EPSILON
#define EPSILON 0.00001
#endif
#define APPROX_EQUAL(a, b) (std::fabs((a) - (b)) < EPSILON)