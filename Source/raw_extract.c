#include <string.h>
#include <assert.h>
#include "raw/raw_tool.h"
#include "sprite/sprite_tool.h"
#include "pal/pal_tool.h"

/** Print instructions to standard output. */
void print_help();

/** Print raw image to standard output as PPM image. */
int print_raw(XeenSprite raw, XeenColor *p);

int main(int argc, char **argv) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		PAL_FILE,
		PAL_READ_FAIL,
	} error = SUCCESS;

	FILE      *pf;
	XeenColor *p;

	if (argc != 3) {
		error = INVALID_ARGS;
		print_help();
		goto end;
	}

	/* Handle arguments */
	if (strncmp(argv[1], "--pal", 5) == 0) {
		if ((pf = fopen(argv[2], "r")) == NULL) {
			error = PAL_FILE;
			goto end;
		}
	} else {
		error = INVALID_ARGS;
		print_help();
		goto end;
	}

	/* Read the palette */
	if (xeen_read_pal(pf, 0, &p)) {
		error = PAL_READ_FAIL;
		goto end;
	}
	assert(p);

	XeenSprite raw = {
		.frames     = 0,
		.cells = 0,
		.map  = NULL,
		.cell       = NULL,
	};

	if ((error = xeen_read_raw(stdin, 0, &raw))) {
		goto end;
	}
	assert(raw.map && raw.cell);

	error = print_raw(raw, p);

end:
	return error;
}

int print_raw(XeenSprite raw, XeenColor *p) {
	enum {
		SUCCESS,
		FWRITE_FAIL,
	} error = SUCCESS;

	XeenFrame f = raw.cell[0];

	/* Print PPM header */
	fprintf(stdout, "P6 %i %i 255\n", f.width, f.height);
	/* And now the data */
	for (int i = 0; i < f.width * f.height; ++i) {
		uint8_t bytes[3] = {
			(p[f.pixels[i]].r << 2) | 0x03,
			(p[f.pixels[i]].g << 2) | 0x03,
			(p[f.pixels[i]].b << 2) | 0x03,
		};
		if (fwrite(bytes, sizeof(uint8_t), 3, stdout) != 3) {
			error = FWRITE_FAIL;
			goto end;
		}
	}

end:
	return error;
}

void print_help() {
	printf("Usage:  raw_extract --pal <palette-file>\n");
	printf("\n");
	printf("The input file is the standard input, the output file the standard output.\n");
}

