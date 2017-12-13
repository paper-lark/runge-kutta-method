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
    return -(point->x * point->x) - point->y;
}

double solution(double x) {
    return -x * x + 2 * x - 2 + 12 * exp(-x);
}

/**
 * Cauchy problem with two equation.
 */
const Point3D initial_conditions3D = {
    .x = 0,
    .u = 1,
    .v = 1
};
double f1(const Point3D *point) {
    return -2 * point->x * point->u * point->u + point->v * point->v - point->x - 1;
}

double f2(const Point3D *point) {
    return 1 / (point->v * point->v) - point->u - point->x / point->u;
}