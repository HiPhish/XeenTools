#include <assert.h>
#include <ctype.h> /* int toupper(int c); */
#include "cc_tool.h"

int xeen_hash_filename(uint16_t *hash, char *name) {
	enum {
		SUCCESS,
		INVALID_ARGS,
	} error = SUCCESS;
	uint16_t h;

	/* Pre-conditions */
	if (!hash || name[0] == '\0') {
		error = INVALID_ARGS;
		goto fail;
	}

	h = toupper(name[0]);

	for (int i = 1; i < 13; ++i) {
		if (name[i] == '\0') {
			goto end;
		}
		/* Rotate the bits in `hash` right 7 places */
		h = (h & 0x007F) << 9 | (h & 0xFF80) >> 7;
		h += toupper(name[i]);
	}

	error = INVALID_ARGS;
	goto fail;

end:
	*hash = h;
	return error;

fail:
	return error;
}

int xeen_cc_file_count(FILE *fp, uint16_t *count) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		FSEEK_FAIL,
		FREAD_FAIL,
	} error = SUCCESS; /* No error. */

	/* Preconditions */
	if (!fp || !count) {
		error = INVALID_ARGS;
		goto end;
	}

	uint8_t byte[2]; /* bytes to be read */

	/* Rewind to start of CC file. */
	if (fseek(fp, 0, SEEK_SET) != 0) {
		//fprintf(stderr, "CC Tool Error: Could not rewind CC file.\n");
		error = FSEEK_FAIL;
		goto end;
	}

	/* Read two bytes as little-endian */
	if (fread(byte, sizeof(uint8_t), 2, fp) != 2) {
		//fprintf(stderr, "CC Tool Error: Could not read CC file count.\n");
		error = FREAD_FAIL;
		goto end;
	}
	*count = ((uint16_t)byte[1] << 8) + (uint16_t)byte[0];

end:
	return error;
}

int xeen_cc_get_toc_entry(FILE *fp, const int index, XeenCCTocEntry *entry) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		FSEEK_FAIL,
		FREAD_FAIL,
	} error = SUCCESS; /* No error. */

	/* Preconditions */
	if (!fp || !entry) {
		error = INVALID_ARGS;
		goto end;
	}

	/* Raw bytes from the file. */
	uint8_t raw[8];
	/* A counter byte is used, and initialized to 0xAC. */
	uint8_t ah = 0xAC + index * 8 * 0x67;
	/* Carry over increments from previous TOC entries. */

	/* Rewind to start of TOC entry. */
	if (fseek(fp, 2 + 8 * index, SEEK_SET) != 0) {
		//fprintf(stderr, "CC Tool Error: Could not rewind CC file.\n");
		error = FSEEK_FAIL;
		goto end;
	}

	/* Read the raw bytes from the file. */
	if (fread(raw, sizeof(uint8_t), 8, fp) != 8) {
		//fprintf(stderr, "CC Tool Error: Could not read CC TOC entry.\n");
		error = FREAD_FAIL;
		goto end;
	}

	/* For each data byte in the TOC array: */
	for (int i = 0; i < 8; ++i) {
		/* Left-rotate the raw byte by two bits. */
		raw[i] = ((raw[i] & 0x3F) << 2) | ((raw[i] & 0xC0) >> 6);
		/* Add the counter byte, ignoring overflow. */
		raw[i] = (uint8_t)((raw[i] + ah) & 0xFF);
		/* The counter byte is incremented by 0x67, overflow is ignored. */
		ah += 0x67;
	}

	/* The padding byte must be 0 */
	assert(raw[7] == 0);

	*entry = (XeenCCTocEntry){
		.file_id     =                            ((uint16_t)raw[1] << 8) + ((uint16_t)raw[0] << 0),
		.file_offset = ((uint32_t)raw[4] << 16) + ((uint32_t)raw[3] << 8) + ((uint32_t)raw[2] << 0),
		.file_length =                            ((uint16_t)raw[6] << 8) + ((uint16_t)raw[5] << 0),
	};

end:
	return error;
}

