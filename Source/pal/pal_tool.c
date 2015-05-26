#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "pal_tool.h"

int xeen_read_pal(FILE *fp, long fo, XeenColor **pal) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		ALLOC_FAIL,
		FREAD_FAIL,
	} error = SUCCESS;

	/* Pre-conditions */
	if(!pal || !fp) {
		/* Error: palette pointer pointer must be valid. */
		error = INVALID_ARGS;
		goto end;
	} else if (*pal) {
		/* Error: palette pointer must be free. */
		error = INVALID_ARGS;
		goto end;
	}

	if (!(*pal = malloc(XEEN_PAL_SIZE * sizeof(XeenColor)))) {
		/* Error: Could not allocate memory. */
		error = ALLOC_FAIL;
		goto end;
	}

	/* Rewind palette file. */
	fseek(fp, fo, SEEK_SET);

	for (int i = 0; i < XEEN_PAL_SIZE; ++i) {
		uint8_t byte[3];
		if (fread(byte, sizeof(uint8_t), 3, fp) != 3) {
			/* Error: could not read three bytes from palette file. */
			error = FREAD_FAIL;
			free(pal);
			pal = NULL;
			goto end;
		}
		(*pal)[i] = (XeenColor) {
			.r = byte[0],
			.g = byte[1],
			.b = byte[2],
		};
	}

	/* Post-condition */
	assert(pal);

end:
	return error;
}

