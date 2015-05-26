#include <assert.h>
#include <stdlib.h>
#include "fac_tool.h"

/** Common function for all three faces, uses a specified limit. */
int xeen_fac_get_frame(int f, int limit, XeenSprite s, XeenFrame *frame, uint8_t t);

int xeen_fac_char_get_frame(enum xeen_char_face f, XeenSprite s, XeenFrame *frame, uint8_t t) {
	return xeen_fac_get_frame(f, XEEN_CHAR_FACES, s, frame, t);
}

int xeen_fac_npc_get_frame(enum xeen_npc_face f, XeenSprite s, XeenFrame *frame, uint8_t t) {
	return xeen_fac_get_frame(f, XEEN_NPC_FACES, s, frame, t);
}

int xeen_fac_dead_get_frame(enum xeen_dead_face f, XeenSprite s, XeenFrame *frame, uint8_t t) {
	return xeen_fac_get_frame(f, XEEN_DEAD_FACES, s, frame, t);
}

int xeen_fac_get_frame(int f, int limit, XeenSprite s, XeenFrame *frame, uint8_t t) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		INVALID_DATA,
	} error = SUCCESS;

	/* Pre-conditions */
	if (!frame || f >= limit) {
		error = INVALID_ARGS;
		goto end;
	} else if (frame->width != 0 || frame->height != 0 || frame->pixels) {
		error = INVALID_ARGS;
		goto end;
	}

	if ((error = xeen_get_frame(s, frame, f, t)) != 0) {
		error += 2;
		goto end;
	}

	/* Post-condition */
	assert(frame->pixels);
	if (frame->width != XEEN_FAC_WIDTH || frame->height != XEEN_FAC_HEIGHT) {
		error = INVALID_DATA;
		free(frame->pixels);
		frame->width  = 0;
		frame->height = 0;
		frame->pixels = NULL;
		goto end;
	}

end:
	return error;
}

