/* @author Keller Flint */

#include <stdio.h>
#include "000pixel.h"
#include "030triangle.c"

int main() {
    // Initializes Pixel Graphics
    if (pixInitialize(512, 512, "Pixel Graphics") != 0)
		return 1;
	else {
        double a[2] = {0, 0};
        double b[2] = {6, 0};
        double c[2] = {3, 6};

        double rgb[3] = {1, 0, 0};

        triRender(a, b, c, rgb);

        pixRun();
		return 0;
	}
}
