#include <math.h>
#include "main.h"

/**
 * Cauchy problem with one equation.
 */
const Point2D initial_conditions2D = {
    .x = 0,
    .y = 10
};

double f(const Point2D *point) {
    return sin(point->x) - point->y;
}

double solution(double x) {
    return -0.5 * cos(x) + 0.5 * sin(x) + 21 * exp(-x) / 2;
}

/**
 * Cauchy problem with two equation.
 */
const Point3D initial_conditions3D = {
    .x = 0,
    .u = 3,
    .v = 0
};
double f1(const Point3D *point) {
    return 3 * point->u + 4 * point->v;
}

double f2(const Point3D *point) {
    return 2 * point->u + point->v;
}