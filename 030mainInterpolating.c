/* @author Keller Flint */

#include <stdio.h>
#include "000pixel.h"
#include "020triangle.c"

int main() {
    // Initializes Pixel Graphics
    if (pixInitialize(512, 512, "Pixel Graphics") != 0)
		return 1;
	else {
        // Scales triangle by a factor of m
        double m = 10;
        // Rasterization tests
        //triRender(1 * m, 1 * m, 3 * m, 2 * m, 3 * m, 8 * m, 1, 0, 1); WORKS
        //triRender(5 * m, 11 * m, 3 * m, 4 * m, 8 * m, 7 * m, 0, 0, 1); WORKS
        //triRender(1 * m, 1 * m, 7 * m, 1 * m, 4 * m, 4 * m, 0, 1, 1); WORKS
        //triRender(3 * m, 7 * m, 8 * m, 1 * m, 11 * m, 10 * m, 0, 1, 0); WORKS
        //triRender(3 * m, 2 * m, 11 * m, 1 * m, 3 * m, 8 * m, 1, 0, 0); WORKS
        //triRender(2 * m, 2 * m, 1 * m, 4 * m, 4 * m, 3 * m, 1, 0, 0); WORKS

        //triRender(6 * m, 6 * m, 0 * m, 6 * m, 3 * m, 0 * m, 1, 0, 0); WORKS
        //triRender(0 * m, 0 * m, 6 * m, 0 * m, 3 * m, 6 * m, 1, 0, 0); WORKS
        //triRender(2 * m, 1 * m, 5 * m, 1 * m, 1 * m, 4 * m, 1, 0, 0); WORKS
        //triRender(2 * m, 1 * m, 5 * m, 1 * m, 6 * m, 4 * m, 1, 0, 0); WORKS
        //triRender(1 * m, 3 * m, 4 * m, 1 * m, 3 * m, 3 * m, 1, 0, 0); WORKS

        pixRun();
		return 0;
	}
}
