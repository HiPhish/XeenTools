#include "dat_tool.h"

int xeen_read_sprite_info(FILE *fp, long o, int i, XeenSpriteFrameInfo *info) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		FREAD_FAIL,
	} error = SUCCESS;
	uint8_t bytes[3 * XEEN_SPRITE_DIRECTIONS];

	/* Preconditions */
	if (!fp || !info) {
		error = INVALID_ARGS;
		goto end;
	}

	/* Jump to position */
	if (fseek(fp, o + i*3*XEEN_SPRITE_DIRECTIONS, SEEK_SET) != 0) {
		error = FREAD_FAIL;
		goto end;
	}

	if (fread(bytes, sizeof(uint8_t), 12, fp) != 12 * sizeof(uint8_t)) {
		error = FREAD_FAIL;
		goto end;
	}

	*info = (XeenSpriteFrameInfo) {
		.first = {
			[XEEN_SPRITE_FRONT] = bytes[0 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_FRONT],
			[XEEN_SPRITE_LEFT ] = bytes[0 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_LEFT ],
			[XEEN_SPRITE_BACK ] = bytes[0 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_BACK ],
			[XEEN_SPRITE_RIGHT] = bytes[0 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_RIGHT],
		},
		.flip = {
			[XEEN_SPRITE_FRONT] = bytes[1 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_FRONT],
			[XEEN_SPRITE_LEFT ] = bytes[1 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_LEFT ],
			[XEEN_SPRITE_BACK ] = bytes[1 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_BACK ],
			[XEEN_SPRITE_RIGHT] = bytes[1 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_RIGHT],
		},
		.last = {
			[XEEN_SPRITE_FRONT] = bytes[2 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_FRONT],
			[XEEN_SPRITE_LEFT ] = bytes[2 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_LEFT ],
			[XEEN_SPRITE_BACK ] = bytes[2 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_BACK ],
			[XEEN_SPRITE_RIGHT] = bytes[2 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_RIGHT],
		},
	};

end:
	return error;
}

