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
double findSlope(double a[], double b[]) {
    return (b[1] - a[1])/(b[0] - a[0]);
}

void render(double a0, double a1, double b0, double b1, double c0, double c1, double rgb[]) {

    double a[2] = {a0, a1};
    double b[2] = {b0, b1};
    double c[2] = {c0, c1};

    double x1, x2;
    x1 = a[0];
    x2 = b[0];

    printf("First time x1: %f, x2: %f\n", x1, x2);

    if (c[1] == findLowOfTwo(a[1], c[1])) {
        for (int y = findHigh(a[1], b[1], c[1]); y >= findLow(a[1], b[1], c[1]); y--) {
            printf("y: %d\n", y);
            x1 = x1 - (1/findSlope(a, c));
            x2 = x2 - (1/findSlope(b, c));
            printf("\tx1: %f, x2: %f\n", x1, x2);
            for (int x = x1; x < x2; x++) {
                pixSetRGB(x, y, rgb[0], rgb[1], rgb[2]);
            }
        }
    } else {
        for (int y = findLow(a[1], b[1], c[1]); y <= findHigh(a[1], b[1], c[1]); y++) {
            printf("y: %d\n", y);
            x1 = x1 + (1/findSlope(a, c));
            x2 = x2 + (1/findSlope(b, c));
            printf("\tx1: %f, x2: %f\n", x1, x2);
            for (int x = x1; x < x2; x++) {
                pixSetRGB(x, y, rgb[0], rgb[1], rgb[2]);
            }
        }
    }
}

void triRender(double a[2], double b[2], double c[2], double rgb[3]) {

    double aa[2] = {a[0], a[1]};
    double bb[2] = {b[0], b[1]};
    double cc[2] = {c[0], c[1]};

    if (findMiddle(aa[1], bb[1], cc[1]) == -1) {
        if (aa[1] == findLow(aa[1], bb[1], cc[1]) && cc[1] == findLow(aa[1], bb[1], cc[1])) {
            b[0] = cc[0];
            b[1] = cc[1];
            c[0] = bb[0];
            c[1] = bb[1];
        } else if (bb[1] == findLow(aa[1], bb[1], cc[1]) && cc[1] == findLow(aa[1], bb[1], cc[1])) {
            a[0] = cc[0];
            a[1] = cc[1];
            c[0] = aa[0];
            c[1] = aa[1];
        } else if (aa[1] == findHigh(aa[1], bb[1], cc[1]) && cc[1] == findHigh(aa[1], bb[1], cc[1])) {
            b[0] = cc[0];
            b[1] = cc[1];
            c[0] = bb[0];
            c[1] = bb[1];
        } else if (bb[1] == findHigh(aa[1], bb[1], cc[1]) && cc[1] == findHigh(aa[1], bb[1], cc[1])) {
            a[0] = cc[0];
            a[1] = cc[1];
            c[0] = aa[0];
            c[1] = aa[1];
        }
    } else {
        if (aa[1] == findLow(aa[1], bb[1], cc[1])) {
            b[0] = aa[0];
            b[1] = aa[1];
        } else if (cc[1] == findLow(aa[1], bb[1], cc[1])) {
            b[0] = cc[0];
            b[1] = cc[1];
        }

        if (bb[1] == findMiddle(aa[1], bb[1], cc[1])) {
            a[0] = bb[0];
            a[1] = bb[1];
        } else if (cc[1] == findMiddle(aa[1], bb[1], cc[1])) {
            a[0] = cc[0];
            a[1] = cc[1];
        }

        if (aa[1] == findHigh(aa[1], bb[1], cc[1])) {
            c[0] = aa[0];
            c[1] = aa[1];
        } else if (bb[1] == findHigh(aa[1], bb[1], cc[1])) {
            c[0] = bb[0];
            c[1] = bb[1];
        }
    }

    printf("(%f,%f):(%f,%f):(%f,%f)\n", a[0], a[1], b[0], b[1], c[0], c[1]);

    if (findMiddle(aa[1], bb[1], cc[1]) != -1) {
        printf("Ran for middle\n");
        double a2 = b[0] + ((a[1] - b[1]) * (1/findSlope(b, c)));
        render(findLowOfTwo(a[0], a2), a[1], findHighOfTwo(a[0], a2), a[1], b[0], b[1], rgb);
        render(findLowOfTwo(a[0], a2), a[1], findHighOfTwo(a[0], a2), a[1], c[0], c[1], rgb);
    } else {
        printf("Ran for no middle\n");
        render(findLowOfTwo(a[0], b[0]), a[1], findHighOfTwo(a[0], b[0]), b[1], c[0], c[1], rgb);
    }
}
