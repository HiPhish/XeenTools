#include <stdlib.h>
#include <stdio.h>
#include "raw_tool.h"

#define X  xeen_raw_size[XEEN_X] /**< Width of the image.        */
#define Y  xeen_raw_size[XEEN_Y] /**< Height of the image.       */
#define A  (X * Y)               /**< Surface area of the image. */

uint16_t xeen_raw_size[XEEN_COORDS] = {
	[XEEN_X] = 320,
	[XEEN_Y] = 200,
};

int xeen_read_raw(FILE *fp, long o, XeenSprite *raw) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		MALLOC_FAIL,
		FREAD_FAIL,
	} error = SUCCESS;

	if (!fp || !raw) {
		error = INVALID_ARGS;
		goto end;
	} else if (raw->frames != 0 || raw->cells != 0 || raw->map != NULL || raw->cell != NULL) {
		error = INVALID_ARGS;
		goto end;
	}

	uint8_t     *bytes = malloc(A * sizeof( *bytes ));
	uint16_t (*map)[2] = malloc(1 * sizeof( *map   ));
	XeenFrame   *frame = malloc(1 * sizeof( *frame ));

	if (!bytes || !map || !frame) {
		error = MALLOC_FAIL;
		goto end;
	}

	if (fread(bytes, sizeof(uint8_t), X * Y, fp) != A * sizeof(uint8_t)) {
		error = FREAD_FAIL;
		free(bytes);
		free(map);
		free(frame);
		goto end;
	}

	*map[0] = *map[1] = 0;
	*frame = (XeenFrame) {
		.width  = X,
		.height = Y,
		.pixels = bytes,
	};

	*raw = (XeenSprite) {
		.frames = 1,
		.cells  = 1,
		.map    = map,
		.cell   = frame,
	};

end:
	return error;
}
