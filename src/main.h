/**
 * Constants and Types.
 */
#pragma once

typedef enum {
    Standalone, System
} Task;

typedef enum {
    Second, Fourth
} Method;

enum {
    BUFF_LEN = 1024
};

typedef struct Point2D {
    double x;
    double y;
} Point2D;

typedef struct Point3D {
    double x;
    double u;
    double v;
} Point3D;