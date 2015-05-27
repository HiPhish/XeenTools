#include <assert.h>
#include "fnt/fnt_tool.h"

void print_help();

int print_font(XeenFont *fnt);

int main(int argc, char **argv) {
	enum {
		SUCCESS,
		FREAD_FAIL,
		PRINT_FAIL,
	} error = SUCCESS;

	XeenFont fnt = xeen_fnt_init();

	if (xeen_read_font(stdin, 0, &fnt)) {
		error = FREAD_FAIL;
	}

	print_font(&fnt);

	return error;
}

int print_font(XeenFont *fnt) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		FWRITE_FAIL,
	} error = SUCCESS;

	if (!fnt) {
		error = INVALID_ARGS;
		goto end;
	}

	for (unsigned char c = 0x00; c < 0x7F; ++c) {
		char string [2] = {c , '\0'};
		printf("%s: (%i | %i)\n", string, fnt->spc[c][XEEN_TYPE_LARGE], fnt->spc[c][XEEN_TYPE_SMALL]);
		printf("  +--------+--------+\n");
		for (int l = 0; l < XEEN_GLYPH_LINES; ++l) {
			char c_map[4] = {
				[0] = ' ',
				[1] = '1',
				[2] = '2',
				[3] = '3',
			};
			printf("  |"); /* Leading bar */
			#define PRINT_LINE(glyph) \
				for (int j = 0; j < XEEN_GLYPH_LINE_PIXELS; ++j) { \
					int i = (fnt->chr[c][glyph][l] & (0xC000 >> XEEN_GLYPH_PIXEL_SIZE*j)) >> XEEN_GLYPH_PIXEL_SIZE*(XEEN_GLYPH_LINE_PIXELS-j-1); \
					assert(i < 4); \
					char i_string[2] = {c_map[i], '\0'}; \
					printf("%s", i_string); \
				} \

			PRINT_LINE(XEEN_TYPE_LARGE)
			printf("|"); /* Separating bar */
			PRINT_LINE(XEEN_TYPE_SMALL)
			#undef PRINT_LINE
			printf("|\n"); /* Finishing bar */
		}
		printf("  +--------+--------+\n");
	}

end:
	return error;
}
