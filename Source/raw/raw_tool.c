#include <stdlib.h>
#include <stdio.h>
#include "raw_tool.h"

#define X xeen_raw_size[XEEN_X]
#define Y xeen_raw_size[XEEN_Y]
#define A (X * Y)

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
	} else if (raw->frames != 0 || raw->cell_count != 0 || raw->frame_map != NULL || raw->cell != NULL) {
		error = INVALID_ARGS;
		goto end;
	}

	uint8_t            *bytes = malloc(A * sizeof(uint8_t));
	XeenSpriteFrameMap *map   = malloc(1 * sizeof(*map   ));
	XeenFrame          *frame = malloc(1 * sizeof(*frame ));

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

	*map = (XeenSpriteFrameMap){.cell = { [0] = 0, [1] = 0 } };
	*frame = (XeenFrame) {
		.width  = X,
		.height = Y,
		.pixels = bytes,
	};

	*raw = (XeenSprite) {
		.frames     = 1,
		.cell_count = 1,
		.frame_map  = map,
		.cell       = frame,
	};

end:
	return error;
}
