#include <assert.h>
#include "att_tool.h"

int xeen_att_get_frame(enum xeen_att_frame f, XeenSprite s, XeenFrame *frame, uint8_t t) {
	enum {
		SUCCESS,
		INVALID_ARGS,
	} error = SUCCESS;

	/* Pre-conditions */
	if (!frame || f >= XEEN_ATT_FRAMES) {
		error = INVALID_ARGS;
		goto end;
	} else if (frame->width != 0 || frame->height != 0 || frame->pixels) {
		error = INVALID_ARGS;
		goto end;
	}

	if ((error = xeen_get_frame(s, frame, f, t)) != 0) {
		error += 1;
		goto end;
	}

	/* Post-condition */
	assert(frame->pixels);

end:
	return error;
}

