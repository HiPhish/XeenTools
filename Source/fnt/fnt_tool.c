#include "fnt_tool.h"

int xeen_read_font(FILE *fp, long o, XeenFont *fnt) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		FREAD_FAIL,
	} error = SUCCESS;

	/* Pre-conditions */
	if (!fp || !fnt) {
		error = INVALID_ARGS;
		goto end;
	}

	if (fseek(fp, o, SEEK_SET)) {
		error = FREAD_FAIL;
		goto end;
	}

	/* Read the characters */
	for (int i = 0; i < XEEN_TYPEFACES; ++i) {
		for (int j = 0; j < XEEN_FNT_CHARS; ++j) {
			uint8_t  bytes[XEEN_GLYPH_LINES][2];
			uint16_t lines[XEEN_GLYPH_LINES];
			if (fread(bytes, sizeof(uint8_t), 16, fp) != 16 * sizeof(uint8_t)) {
				error = FREAD_FAIL;
				goto end;
			}
			/* Order endianess */
			for (int k = 0; k < XEEN_GLYPH_LINES; ++k) {
				lines[k] = ((uint16_t)bytes[k][1] << 8) + (uint16_t)bytes[k][0];
			}
			/* Reverse every line, but keep pairs together */
			for (int k = 0; k < XEEN_GLYPH_LINES; ++k) {
				uint16_t temp = 0x0000;
				uint16_t mask = 0x0003; /* 0b0000000000000011 */
				for (int l = 0; l < XEEN_GLYPH_LINE_PIXELS; ++l) {
					temp  |= (lines[k] & mask) >> 2 * l;
					mask <<= 2;
					if (l != 8 - 1) {
						temp <<= 2;
					}
				}
				lines[k] = temp;
			}
			/* Assign character */
			for (int k = 0; k < XEEN_GLYPH_LINES; ++k) {
				fnt->chr[j][i][k] = lines[k];
			}
		}
	}

	/* Read the spacing */
	#define CHARS (XEEN_FNT_CHARS * XEEN_TYPEFACES) 
	if (fread(fnt->spc, sizeof(uint8_t), sizeof(uint8_t) * CHARS, fp) != sizeof(uint8_t) * CHARS) {
		error = FREAD_FAIL;
		goto end;
	}
	#undef CHARS

end:
	return error;
}

XeenFont xeen_fnt_init() {
	XeenFont fnt;
	for (int i = 0; i < XEEN_FNT_CHARS; ++i) {
		for (int j = 0; j < XEEN_TYPEFACES; ++j) {
			for (int k = 0; k < XEEN_GLYPH_LINES; ++k) {
				fnt.chr[i][j][k] = 0x0000;
			}
			fnt.spc[i][j] = 0x00;
		}
	}
	return fnt;
}

