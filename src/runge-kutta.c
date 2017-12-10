#include <math.h>
#include "main.h"

/**
 * Exports.
 */
extern double f(const Point2D *point);
extern double f1(const Point3D *point);
extern double f2(const Point3D *point);
extern const Point2D initial_conditions2D;
extern const Point3D initial_conditions3D;

/**
 * Second-order Runge-Kutta method for a standalone equation.
 */
void rk2_standalone(Point2D *table, unsigned n, double h, double a) {
    /**
     * Set initial conditions.
     */
    table[0].y = initial_conditions2D.y;

    /**
     * Fill in the table.
     */
    for (unsigned i = 1; i < n; i++) {
        Point2D *previous = &(table[i-1]);
        double k1 = f(previous);
        Point2D point = {
            .x = previous->x + h / (2 * a),
            .y = previous->y + h * k1 / (2 * a)
        };
        double k2 = f(&point);
        double v3 = (1 - a) * k1 + a * k2;
        table[i].y = previous->y + h * v3;
    }
}

/**
 * Fourth-order Runge-Kutta method for a standalone equation.
 */
void rk4_standalone(Point2D *table, unsigned n, double h) {
    /**
     * Set initial conditions.
     */
    table[0].y = initial_conditions2D.y;

    /**
     * Fill in the table.
     */
    for (unsigned i = 1; i < n; i++) {
        Point2D point = {
            .x = table[i - 1].x,
            .y = table[i - 1].y
        };
        double k1 = f(&point);

        point.x = table[i - 1].x + h / 2;
        point.y = table[i - 1].y + h * k1 / 2;
        double k2 = f(&point);

        point.y = table[i - 1].y + h * k2 / 2;
        double k3 = f(&point);

        point.x = table[i - 1].x + h;
        point.y = table[i - 1].y + h * k3;
        double k4 = f(&point);

        table[i].y = table[i - 1].y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    }
}

/**
 * Second-order Runge-Kutta method for a system of equations.
 */
void rk2_system(Point3D *table, unsigned n, double h) {
     /**
     * Set initial conditions.
     */
    table[0].u = initial_conditions3D.u;
    table[0].v = initial_conditions3D.v;

    /**
     * Fill in the table.
     */
    for (unsigned i = 1; i < n; i++) {
        Point3D point = table[i - 1];
        double k1 = f1(&point);
        double m1 = f2(&point);

        point.x = table[i - 1].x + h;
        point.u = table[i - 1].u + h * k1;
        point.v = table[i - 1].v + h * m1;
        double k2 = f1(&point);
        double m2 = f2(&point);

        table[i].u = table[i - 1].u + h * (m1 + k2) / 2;
        table[i].v = table[i - 1].v + h * (k1 + m2) / 2;
    }
}

/**
 * Fourth-order Runge-Kutta method for a system of equations.
 */
void rk4_system(Point3D *table, unsigned n, double h) {
    /**
     * Set initial conditions.
     */
    table[0].u = initial_conditions3D.u;
    table[0].v = initial_conditions3D.v;

    /**
     * Fill in the table.
     */
    for (unsigned i = 1; i < n; i++) {
        Point3D point = table[i - 1];
        double k1 = f1(&point);
        double m1 = f2(&point);

        point.x = table[i - 1].x + h / 2;
        point.u = table[i - 1].u + h * k1 / 2;
        point.v = table[i - 1].v + h * m1 / 2;
        double k2 = f1(&point);
        double m2 = f2(&point);

        point.x = table[i - 1].x + h / 2;
        point.u = table[i - 1].u + h * k2 / 2;
        point.v = table[i - 1].v + h * m2 / 2;
        double k3 = f1(&point);
        double m3 = f2(&point);

        point.x = table[i - 1].x + h;
        point.u = table[i - 1].u + h * k3;
        point.v = table[i - 1].v + h * m3;
        double k4 = f1(&point);
        double m4 = f2(&point);

        table[i].u = table[i - 1].u + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        table[i].v = table[i - 1].v + h * (m1 + 2 * m2 + 2 * m3 + m4) / 6;
    }
}