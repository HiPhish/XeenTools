#include <assert.h>
#include "mon_tool.h"

int xeen_mon_get_frame(enum xeen_mon_frame f, XeenSprite s, XeenFrame *frame, uint8_t t) {
	enum {
		SUCCESS,
		INVALID_ARGS,
	} error = SUCCESS;

	if (!frame || f >= XEEN_MON_FRAMES) {
		error = INVALID_ARGS;
		goto end;
	} else if (frame->pixels) {
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
