/* @author Keller Flint */

#include <stdio.h>
#include "000pixel.h"
#include "030triangle.c"

int main() {
    // Initializes Pixel Graphics
    if (pixInitialize(512, 512, "Pixel Graphics") != 0)
		return 1;
	else {

        double m = 10;

        double a[2] = {0 * m, 0 * m};
        double b[2] = {6 * m, 0 * m};
        double c[2] = {3 * m, 6 * m};

        double rgb[3] = {1, 0, 0};

        triRender(a, b, c, rgb);

        pixRun();
		return 0;
	}
}
