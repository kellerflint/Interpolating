/* @author Keller Flint */


#include <stdio.h>
#include <math.h>


//Global variables for now because interpolation MESSED UP MY COOL SOLUTION
double globalA0, globalA1, globalB0, globalB1, globalC0, globalC1;

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

void render(double a0, double a1, double b0, double b1, double c0, double c1, double rgb[3],
        double alpha[3], double beta[3], double gamma[3]) {

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
                double m[2][2] = {
                    {globalB0 - globalA0, globalC0 - globalA0},
                    {globalB1 - globalA1, globalC1 - globalA1}};
                double mInv[2][2];
                double xa[2] = {x - globalA0, y - globalA1};
                printf("%f, %f\n", xa[0], xa[1]);
                double pq[2];
                if (mat22Invert(m, mInv) != 0) {
                    mat221Multiply(mInv, xa, pq);
                } else {
                    printf("DETERMINANT WAS 0. INVERSE MATRIX DOES NOT EXIST!");
                }

                double color[3];
                color[0] = alpha[0] + (pq[0] * (beta[0] - alpha[0])) + (pq[1] * (gamma[0] - alpha[0]));
                color[1] = alpha[1] + (pq[0] * (beta[1] - alpha[1])) + (pq[1] * (gamma[1] - alpha[1]));
                color[2] = alpha[2] + (pq[0] * (beta[2] - alpha[2])) + (pq[1] * (gamma[2] - alpha[2]));

				printf("x:%d, y:%d\n", x, y);
				printf("xa[0]:%f, xa[1]:%f\n", xa[0], xa[1]);
				printf("color[0]:%f, color[1]:%f, color[2]:%f\n", color[0], color[1], color[2]);

                pixSetRGB(x, y, color[0], color[1], color[2]);
            }
        }
    } else {
        for (int y = findLow(a[1], b[1], c[1]); y <= findHigh(a[1], b[1], c[1]); y++) {
            printf("y: %d\n", y);
            x1 = x1 + (1/findSlope(a, c));
            x2 = x2 + (1/findSlope(b, c));
            printf("\tx1: %f, x2: %f\n", x1, x2);
            for (int x = x1; x < x2; x++) {
                double m[2][2] = {
                    {globalB0 - globalA0, globalC0 - globalA0},
                    {globalB1 - globalA1, globalC1 - globalA1}};
                double mInv[2][2];
                double xa[2] = {x - globalA0, y - globalA1};
                printf("%f, %f\n", xa[0], xa[1]);
                double pq[2];
                if (mat22Invert(m, mInv) != 0) {
                    mat221Multiply(mInv, xa, pq);
                } else {
                    printf("DETERMINANT WAS 0. INVERSE MATRIX DOES NOT EXIST!");
                }

				/*
				printf("alpha[0]:%f, alpha[1]:%f, alpha[2]:%f||beta[0]:%f, beta[1]:%f,
				 		beta[2]:%f||gamma[0]:%f, gamma[1]:%f, gamma[2]:%f\n", alpha[0],
						alpha[1], alpha[2], beta[0], beta[1], beta[2], gamma[0], gamma[1], gamma[2]);
				*/

				printf("pq[0]:%f, pq[1]:%f\n", pq[0], pq[1]);

                double color[3];
                color[0] = alpha[0] + (pq[0] * (beta[0] - alpha[0])) + (pq[1] * (gamma[0] - alpha[0]));
                color[1] = alpha[1] + (pq[0] * (beta[1] - alpha[1])) + (pq[1] * (gamma[1] - alpha[1]));
                color[2] = alpha[2] + (pq[0] * (beta[2] - alpha[2])) + (pq[1] * (gamma[2] - alpha[2]));

				printf("x:%d, y:%d\n", x, y);
				printf("xa[0]:%f, xa[1]:%f\n", xa[0], xa[1]);
				printf("color[0]:%f, color[1]:%f, color[2]:%f\n", color[0], color[1], color[2]);
				printf("------\n");

                pixSetRGB(x, y, color[0], color[1], color[2]);
            }
        }
    }
}

void triRender(double a[2], double b[2], double c[2], double rgb[3],
        double alpha[3], double beta[3], double gamma[3]) {


    double aa[2] = {a[0], a[1]};
    double bb[2] = {b[0], b[1]};
    double cc[2] = {c[0], c[1]};

	double alpha2[3] = {alpha[0], alpha[1], alpha[2]};
	double beta2[3] = {beta[0], beta[1], beta[2]};
	double gamma2[3] = {gamma[0], gamma[1], gamma[2]};

    if (findMiddle(aa[1], bb[1], cc[1]) == -1) {
        if (aa[1] == findLow(aa[1], bb[1], cc[1]) && cc[1] == findLow(aa[1], bb[1], cc[1])) {
            b[0] = cc[0];
            b[1] = cc[1];
            c[0] = bb[0];
            c[1] = bb[1];

			beta = gamma2;
			gamma = beta;
        } else if (bb[1] == findLow(aa[1], bb[1], cc[1]) && cc[1] == findLow(aa[1], bb[1], cc[1])) {
            a[0] = cc[0];
            a[1] = cc[1];
            c[0] = aa[0];
            c[1] = aa[1];

			alpha = gamma2;
			gamma = alpha2;
        } else if (aa[1] == findHigh(aa[1], bb[1], cc[1]) && cc[1] == findHigh(aa[1], bb[1], cc[1])) {
            b[0] = cc[0];
            b[1] = cc[1];
            c[0] = bb[0];
            c[1] = bb[1];

			beta = gamma2;
			gamma = beta2;
        } else if (bb[1] == findHigh(aa[1], bb[1], cc[1]) && cc[1] == findHigh(aa[1], bb[1], cc[1])) {
            a[0] = cc[0];
            a[1] = cc[1];
            c[0] = aa[0];
            c[1] = aa[1];

			alpha = gamma2;
			gamma = alpha2;
        }
    } else {
        if (aa[1] == findLow(aa[1], bb[1], cc[1])) {
            b[0] = aa[0];
            b[1] = aa[1];

			beta = alpha2;
        } else if (cc[1] == findLow(aa[1], bb[1], cc[1])) {
            b[0] = cc[0];
            b[1] = cc[1];

			beta = gamma2;
        }

        if (bb[1] == findMiddle(aa[1], bb[1], cc[1])) {
            a[0] = bb[0];
            a[1] = bb[1];

			alpha = beta2;
        } else if (cc[1] == findMiddle(aa[1], bb[1], cc[1])) {
            a[0] = cc[0];
            a[1] = cc[1];

			alpha = gamma2;
        }

        if (aa[1] == findHigh(aa[1], bb[1], cc[1])) {
            c[0] = aa[0];
            c[1] = aa[1];

			gamma = alpha2;
        } else if (bb[1] == findHigh(aa[1], bb[1], cc[1])) {
            c[0] = bb[0];
            c[1] = bb[1];

			gamma = beta2;
        }
    }

	// Assign global variables for a, b and c
	globalA0 = a[0];
	globalA1 = a[1];
	globalB0 = b[0];
	globalB1 = b[1];
	globalC0 = c[0];
	globalC1 = c[1];

    printf("(%f,%f):(%f,%f):(%f,%f)\n", a[0], a[1], b[0], b[1], c[0], c[1]);

    if (findMiddle(aa[1], bb[1], cc[1]) != -1) {
        printf("Ran for middle\n");
        double a2 = b[0] + ((a[1] - b[1]) * (1/findSlope(b, c)));
        render(findLowOfTwo(a[0], a2), a[1], findHighOfTwo(a[0], a2), a[1], b[0], b[1], rgb, alpha, beta, gamma);
        render(findLowOfTwo(a[0], a2), a[1], findHighOfTwo(a[0], a2), a[1], c[0], c[1], rgb, alpha, beta, gamma);
    } else {
        printf("Ran for no middle\n");
        render(findLowOfTwo(a[0], b[0]), a[1], findHighOfTwo(a[0], b[0]), b[1], c[0], c[1], rgb, alpha, beta, gamma);
    }
}
