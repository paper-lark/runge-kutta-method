#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "main.h"

/**
 * Exports.
 */
extern const Point2D initial_conditions2D;
extern const Point3D initial_conditions3D;
extern void rk2_standalone(Point2D *table, unsigned n, double h, double a);
extern void rk4_standalone(Point2D *table, unsigned n, double h);
extern void rk2_system(Point3D *table, unsigned n, double h);
extern void rk4_system(Point3D *table, unsigned n, double h);
extern double solution(double x);

/**
 * Function prints formatted function table for standalone equation. 
 */
void print2D(const Point2D *table, unsigned n) {
    printf("       x       |       y       \n");
    printf("-------------------------------\n");
    for (unsigned i = 0; i < n; i++) {
        printf("%14.8g | %14.8g\n", table[i].x, table[i].y);
    }
    printf("\n");
}

/**
 * Function prints formatted function table for system of equations. 
 */
void print3D(const Point3D *table, unsigned n) {
    printf("       x       |       u        |       v       \n");
    printf("------------------------------------------------\n");
    for (unsigned i = 0; i < n; i++) {
        printf("%14.8g | %14.8g | %14.8g\n", table[i].x, table[i].u, table[i].v);
    }
    printf("\n");
}

/**
 * Entry point.
 */
int main(void) {

    /*
     * Read task properties.
     */
    Task task;
    Method method;
    double h;
    double limit;
    
    char *buffer = malloc(BUFF_LEN);
    printf("Enter task: (\"standalone\" for a standalone equation, and \"system\" for a system of equations)\n");
    fgets(buffer, BUFF_LEN, stdin);
    unsigned len = strlen(buffer);
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    if (strcmp(buffer, "standalone") == 0 || strcmp(buffer, "Standalone") == 0) {
        task = Standalone;
    } else if (strcmp(buffer, "system") == 0 || strcmp(buffer, "System") == 0) {
        task = System;
    } else {
        free(buffer);
        fprintf(stderr, "> error: unknown task\n");
        exit(1);
    }

    printf("Enter method: (\"second\" for the second-order Runge-Kutta method, and \"fourth\" for the fourth-order Runge-Kutta method)\n");
    fgets(buffer, BUFF_LEN, stdin);
    len = strlen(buffer);
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    if (strcmp(buffer, "second") == 0 || strcmp(buffer, "Second") == 0) {
        method = Second;
    } else if (strcmp(buffer, "fourth") == 0 || strcmp(buffer, "Fourth") == 0) {
        method = Fourth;
    } else {
        free(buffer);
        fprintf(stderr, "> error: unknown method\n");
        exit(1);
    }
    free(buffer);

    printf("Enter limit of integration:\n");
    scanf("%lf", &limit);
    printf("Enter method step:\n");
    scanf("%lf", &h);
    if (h <= 0) {
        fprintf(stderr, "> error: step should be a positive number\n");
        exit(1);
    }

    /**
     * Start solving according the specified method and task options.
     */
    if (task == Standalone) {
        /**
         * Prepare the table.
         */
        const unsigned n = ceil((limit - initial_conditions2D.x) / h);
        assert(n > 0);
        Point2D *table = malloc(n * sizeof(table[0]));
        for (unsigned i = 0; i < n; i++) {
            table[i].x = i == 0 ? initial_conditions2D.x : table[i - 1].x + h;
            table[i].y = solution(table[i].x);
        }

        /**
         * Print precise solution
         */
        print2D(table, n);
        /**
         * Calculate approximation and print it.
         */
        if (method == Second) {
            /**
             * Read parameter value.
             */
            double a;
            printf("Enter parameter value:\n");
            scanf("%lf", &a);
            if (a <= 0 || a > 1) {
                fprintf(stderr, "> error: paraneter should be in range (0, 1]\n");
                exit(1);
            }
            rk2_standalone(table, n, h, a);
        } else if (method == Fourth) {
            rk4_standalone(table, n, h);
        }
        print2D(table, n);

    } else if (task == System) {
        /**
         * Prepare the table.
         */
        const unsigned n = ceil((limit - initial_conditions3D.x) / h);
        Point3D *table = malloc(n * sizeof(table[0]));
        for (unsigned i = 0; i < n; i++) {
            table[i].x = i == 0 ? initial_conditions3D.x : table[i - 1].x + h;
        }
        /**
         * Calculate approximation and print it.
         */
        if (method == Second) {
            rk2_system(table, n, h);
        } else if (method == Fourth) {
            rk4_system(table, n, h);
        }
        print3D(table, n);
    } else {
        assert(0);
    }

    /**
     * Print completion message.
     */
    printf("Done!");
}