#include <math.h>
#include "main.h"

/**
 * Cauchy problem with one equation.
 */
const Point2D initial_conditions2D = {
    .x = 0,
    .y = 0
};

double f(const Point2D *point) {
    return 3 -point->x - point->y;
}

double solution(double x) {
    return 4 - x - 4 * exp(-x);
}

/**
 * Cauchy problem with two equation.
 */
const Point3D initial_conditions3D = {
    .x = 1,
    .u = 1,
    .v = 1
};
double f1(const Point3D *point) {
    return (point->u - point->v) / point->x;
}

double f2(const Point3D *point) {
    return (point->u + point->v) / point->x;
}