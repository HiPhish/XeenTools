#include "cpp_tool.h"

/** Length of the copy protection data. */
#define LENGTH  (3 + XEEN_CPP_LENGTH)

int xeen_read_copy_protection(FILE *fp, long o, int index, XeenCopyProtection *prot) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		FREAD_FAIL,
		INVALID_DATA,
	} error = SUCCESS;

	uint8_t bytes[LENGTH];
	/** Counter byte for decryption. */
	uint8_t counter = (index * 16); /* will loop around */

	/* Pre-conditions */
	if (!fp || !prot) {
		error = INVALID_ARGS;
		goto end;
	} else if (prot->line != 0 || prot->page != 0 || prot->word != 0 || prot->string[0] != '\0') {
		error = INVALID_ARGS;
		goto end;
	}

	/* Jump to index */
	if (fseek(fp, o + LENGTH * index, SEEK_SET)) {
		error = FREAD_FAIL;
		goto end;
	}

	/* Read bytes */
	if (fread(bytes, sizeof(uint8_t), LENGTH, fp) != sizeof(uint8_t) * LENGTH) {
		error = FREAD_FAIL;
		goto end;
	}

	/* Decrypt the bytes */
	for (int i = 0; i < LENGTH; ++i) {
		bytes[i] ^= (counter++);
	}

	/* Post-condition */
	if (bytes[LENGTH - 1] != '\0') {
		error = INVALID_DATA;
		goto end;
	}

	*prot = (XeenCopyProtection) {
		.page = bytes[0],
		.line = bytes[1],
		.word = bytes[2],
	};

	for (int i = 0; i < XEEN_CPP_LENGTH; ++i) {
		prot->string[i] = bytes[3+i];
	}

end:
	return error;
}

