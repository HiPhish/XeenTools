#include <stdlib.h>
#include <assert.h>

#include "pal/pal_tool.h"

void print_help();

int print_palette(XeenColor *palette);

int main(int argc, char **argv) {
	enum {
		SUCCESS,
		PAL_READ_FAIL,
		PRINT_FAIL,
	} error = SUCCESS;

	XeenColor *palette = NULL;

	/* Read the palette */
	if (xeen_read_pal(stdin, 0, &palette)) {
		error = PAL_READ_FAIL;
		goto end;
	}
	assert(palette);

	if (print_palette(palette)) {
		error = PRINT_FAIL;
		goto end;
	}

end:
	return error;
}

int print_palette(XeenColor *palette) {
	#define WIDTH   16 /* Width of coloured block in the picture.  */
	#define HEIGHT  16 /* Height of coloured block in the picture. */
	enum {
		SUCCESS,
		FWRITE_FAIL,
	} error = SUCCESS;

	/* Print PPM header */
	fprintf(stdout, "P6 %i %i 255\n", 16 * WIDTH, 16 * HEIGHT);

	for (int y = 0; y < HEIGHT * 16; ++y) {
		for (int x = 0; x < WIDTH * 16; ++x) {
			XeenColor c = palette[(y/16) * 16 + (x/16)];
			uint8_t bytes[3] = {
				[0] = (c.r << 2) | 0x03,
				[1] = (c.g << 2) | 0x03,
				[2] = (c.b << 2) | 0x03,
			};
			if (fwrite(bytes, sizeof(uint8_t), 3, stdout) != 3 * sizeof(uint8_t)) {
				error = FWRITE_FAIL;
				goto end;
			}
		}
	}

end:
	return error;
	#undef WIDTH
	#undef HEIGHT
}


