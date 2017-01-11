/* @author Keller Flint */

#include <stdio.h>
#include "000pixel.h"
#include "030triangle.c"

int main() {
    // Initializes Pixel Graphics
    if (pixInitialize(512, 512, "Pixel Graphics") != 0)
		return 1;
	else {
        // TODO

        pixRun();
		return 0;
	}
}
