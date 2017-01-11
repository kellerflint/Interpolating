/* @author Keller Flint */


#include <stdio.h>
#include "000pixel.h"
#include <math.h>


/* Returns the highest value of three doubles */
double findHigh(double x, double y, double z) {
    double high = x;

    if (y > high)
        high = y;
    if (z > high)
        high = z;

    return high;
}

double findHighOfTwo(double x, double y) {
    if (x > y)
        return x;
    else
        return y;
}

double findLowOfTwo(double x, double y) {
    if (x < y)
        return x;
    else
        return y;
}

/* Returns the loweset value of three doubles */
double findLow(double x, double y, double z) {
    double low = x;

    if (y < low)
        low = y;
    if (z < low)
        low = z;

    return low;
}

/* Returns the middle value in a set of three doubles */
double findMiddle(double x, double y, double z) {
    if (x != findLow(x, y, z) && x != findHigh(x, y, z))
        return x;
    if (y != findLow(x, y, z) && y != findHigh(x, y, z))
        return y;
    if (z != findLow(x, y, z) && z != findHigh(x, y, z))
        return z;
    return -1;
}

/* Returns the slope of a line given two points */
double findSlope(double a0, double a1, double b0, double b1) {
    return (b1 - a1)/(b0 - a0);
}

void render(double a0, double a1, double b0, double b1, double c0, double c1, double r, double g, double b) {
    double x1, x2;
    x1 = a0;
    x2 = b0;

    printf("First time x1: %f, x2: %f\n", x1, x2);

    if (c1 == findLowOfTwo(a1, c1)) {
        for (int y = findHigh(a1, b1, c1); y >= findLow(a1, b1, c1); y--) {
            printf("y: %d\n", y);
            x1 = x1 - (1/findSlope(a0, a1, c0, c1));
            x2 = x2 - (1/findSlope(b0, b1, c0, c1));
            printf("\tx1: %f, x2: %f\n", x1, x2);
            for (int x = x1; x < x2; x++) {
                pixSetRGB(x, y, r, g, b);
            }
        }
    } else {
        for (int y = findLow(a1, b1, c1); y <= findHigh(a1, b1, c1); y++) {
            printf("y: %d\n", y);
            x1 = x1 + (1/findSlope(a0, a1, c0, c1));
            x2 = x2 + (1/findSlope(b0, b1, c0, c1));
            printf("\tx1: %f, x2: %f\n", x1, x2);
            for (int x = x1; x < x2; x++) {
                pixSetRGB(x, y, r, g, b);
            }
        }
    }
}

void triRender(double a0, double a1, double b0, double b1, double c0, double c1, double red, double green, double blue) {

    double a[2] = {a0, a1};
    double b[2] = {b0, b1};
    double c[2] = {c0, c1};

    if (findMiddle(a[1], b[1], c[1]) == -1) {
        if (a[1] == findLow(a[1], b[1], c[1]) && c[1] == findLow(a[1], b[1], c[1])) {
            b0 = c[0];
            b1 = c[1];
            c0 = b[0];
            c1 = b[1];
        } else if (b[1] == findLow(a[1], b[1], c[1]) && c[1] == findLow(a[1], b[1], c[1])) {
            a0 = c[0];
            a1 = c[1];
            c0 = a[0];
            c1 = a[1];
        } else if (a[1] == findHigh(a[1], b[1], c[1]) && c[1] == findHigh(a[1], b[1], c[1])) {
            b0 = c[0];
            b1 = c[1];
            c0 = b[0];
            c1 = b[1];
        } else if (b[1] == findHigh(a[1], b[1], c[1]) && c[1] == findHigh(a[1], b[1], c[1])) {
            a0 = c[0];
            a1 = c[1];
            c0 = a[0];
            c1 = a[1];
        }
    } else {
        if (a[1] == findLow(a[1], b[1], c[1])) {
            b0 = a[0];
            b1 = a[1];
        } else if (c[1] == findLow(a[1], b[1], c[1])) {
            b0 = c[0];
            b1 = c[1];
        }

        if (b[1] == findMiddle(a[1], b[1], c[1])) {
            a0 = b[0];
            a1 = b[1];
        } else if (c[1] == findMiddle(a[1], b[1], c[1])) {
            a0 = c[0];
            a1 = c[1];
        }

        if (a[1] == findHigh(a[1], b[1], c[1])) {
            c0 = a[0];
            c1 = a[1];
        } else if (b[1] == findHigh(a[1], b[1], c[1])) {
            c0 = b[0];
            c1 = b[1];
        }
    }

    printf("(%f,%f):(%f,%f):(%f,%f)\n", a0, a1, b0, b1, c0, c1);

    if (findMiddle(a[1], b[1], c[1]) != -1) {
        printf("Ran for middle\n");
        double a2 = b0 + ((a1 - b1) * (1/findSlope(b0, b1, c0, c1)));
        render(findLowOfTwo(a0, a2), a1, findHighOfTwo(a0, a2), a1, b0, b1, red, green, blue);
        render(findLowOfTwo(a0, a2), a1, findHighOfTwo(a0, a2), a1, c0, c1, red, green, blue);
    } else {
        printf("Ran for no middle\n");
        render(findLowOfTwo(a0, b0), a1, findHighOfTwo(a0, b0), b1, c0, c1, red, green, blue);
    }
}
