#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "cc_tool/cc_tool.h"

/* Instruction strings */
#define PRINT_HELP   "--help            "
#define PRINT_HASH   "--print-hash      "
#define PRINT_FCOUNT "--print-file-count"
#define PRINT_TOC    "--print-toc       "
#define PRINT_FNAME  "--print-by-name   "
#define PRINT_FID    "--print-by-id     "

/** Return codes for the CC extractor. */
typedef enum return_codes {
	SUCCESS,  /**< No error.          */
	CC_ERROR, /**< CC tool failed.    */
	ARGS,     /**< Invalid arguments. */
} ReturnCode;

/** Print the CC file table of contents.
 *
 *  @param count  File count of the CC file.
 *
 *  @return  Error code.
 */
int print_toc(uint16_t count);

/** Print the hash of a file name.
 *
 *  @param name  File name to hash.
 *
 *  @return  Error code.
 */
int print_hash(char *name);

/** Print file contents by file name.
 *
 *  @param name   Name of the file.
 *  @param count  Number of files in the CC file.
 *  @param xor    Byte to XOR file bytes with.
 *
 *  @return  Error code.
 *
 *  If you don't want to XOR bytes pass a value of `0x00`.
 */
int print_file_by_name(char *name, uint16_t count, uint8_t xor);

/** Print file contents by file ID.
 *
 *  @param id     ID of the file.
 *  @param count  Number of files in the CC file.
 *  @param xor    Byte to XOR file bytes with.
 *
 *  @return  Error code.
 *
 *  If you don't want to XOR bytes pass a value of `0x00`.
 */
int print_file_by_id(uint16_t id, uint16_t count, uint8_t xor);

/* Print usage instructions. */
void print_help(void);

/** Helper that converts a string to an unsigned 16-bit integer.
 *
 *  @param a  String to parse.
 *  @param h  Pointer to the number to store.
 *
 *  @return  Error code.
 *
 *  This function is case-insensitive.
 */
int atoh16(char *a, uint16_t *h);

int main(int argc, char **argv) {
	ReturnCode error = SUCCESS;
	uint16_t fcount; /* File count of CC file */

	/* Handle arguments */
	if (argc < 2) {
		print_help();
		goto end;
	}

	if (argc == 2 && strncmp(argv[1], PRINT_HELP, 6) == 0) {
		print_help();
		goto end;
	}

	if (argc == 3 && strncmp(argv[1], PRINT_HASH, 12) == 0) {
		error = print_hash(argv[2]);
		goto end;
	}

	/* The following instructions need the file count. */
	if (xeen_cc_file_count(stdin, &fcount) != 0) {
		error = CC_ERROR;
		fprintf(stderr, "Error: Could not read file count from CC file.\n");
		goto end;
	}

	if (argc == 2 && strncmp(argv[1], PRINT_FCOUNT, 18) == 0) {
		printf("Number of files in CC file: %i\n", fcount);
		goto end;
	}

	if (argc == 2 && strncmp(argv[1], PRINT_TOC, 11) == 0) {
		error = print_toc(fcount);
		goto end;
	}

	if (argc == 4 && strncmp(argv[1], PRINT_FNAME, 15) == 0) {
		uint8_t xor = strncmp(argv[3], "true", 4) == 0 ? XEEN_CC_XOR_VAL : 0x00;
		error = print_file_by_name(argv[2], fcount, xor);
		goto end;
	}

	if (argc == 4 && strncmp(argv[1], PRINT_FID, 13) == 0) {
		uint8_t  xor = strncmp(argv[3], "true", 4) == 0 ? XEEN_CC_XOR_VAL : 0x00;
		uint16_t  id;
		error = atoh16(argv[2], &id);
		if (error) {
			goto end;
		}
		error = print_file_by_id(id, fcount, xor);
		goto end;
	}

	/* No match, defaulting to error */
	fprintf(stderr, "Error: invalid arguments, aborting.\n");
	error = ARGS;
	print_help();

end:
	return error;
}

int print_toc(uint16_t count) {
	ReturnCode error = SUCCESS;
	XeenCCTocEntry entry;

	/* Loop over the TOC entries */
	for (uint16_t i = 0; i < count; ++i) {
		if (xeen_cc_get_toc_entry(stdin, i, &entry) != 0) {
			error = 1;
			fprintf(stderr, "Error: Could not read TOC entry %i.\n", i);
			goto end;
		}

		printf(
			"ID: 0x%04X   Offset: 0x%06X   Length: %i\n",
			entry.file_id, entry.file_offset, entry.file_length
		);
	}

end:
	return error;
}

int print_hash(char *name) {
	ReturnCode error = SUCCESS;
	uint16_t id;

	if (xeen_hash_filename(&id, name) != 0) {
		error = 1;
		fprintf(stderr, "Error: Could not hash file name:\n  %s\n", name);
		goto end;
	}

	printf("Name: %s   Hash: 0x%04X\n", name, id);

end:
	return error;
}

int print_file_by_name(char *name, uint16_t count, uint8_t xor) {
	ReturnCode error = SUCCESS;
	uint16_t id;

	if (xeen_hash_filename(&id, name) != 0) {
		error = 1;
		fprintf(stderr, "Error: Could not hash file name:\n  %s\n", name);
		goto end;
	}

	error = print_file_by_id(id, count, xor);

end:
	return error;
}

int print_file_by_id(uint16_t id, uint16_t count, uint8_t xor) {
	ReturnCode error = SUCCESS;
	XeenCCTocEntry entry;
	uint8_t byte;

	/* Loop through the TOC entries */
	for (uint16_t i = 0; i < count; ++i) {
		if (xeen_cc_get_toc_entry(stdin, i, &entry) != 0) {
			error = 1;
			fprintf(stderr, "Error reading the CC TOC entries, aborting.\n");
			goto end;
		}
		if (entry.file_id == id) {
			goto found_id;
		}
	}
	/* The ID has not been found */
	error = 2;
	fprintf(stderr, "Error: Could not find the file with ID:\n  %i\n", id);
	goto end;

found_id:
	/* Move the CC file position to the offset of the file. */
	fseek(stdin, entry.file_offset, SEEK_SET);
	/* Read and write bytes */
	for (int i = 0; i < entry.file_length; ++i) {
		if (fread(&byte, sizeof(uint8_t), 1, stdin) != 1) {
			error = 1;
			fprintf(stderr, "Error: could not read byte %i from CC file.\n", i);
			goto end;
		}
		/* If the value is 0x00 nothing will happen */
		byte ^= xor;
		if (fwrite(&byte, sizeof(uint8_t), 1, stdout) != 1) {
			error = 1;
			fprintf(stderr, "Error: could not write byte %i to file.\n", i);
			goto end;
		}
	}

end:
	return error;
}

void print_help() {
	printf(
		"Usage: cc_extract --instruction [arguments]\n"
		"\n"
		"The program is run by providing an instruction as the first argument followed\n"
		"by arguments for that instruction. Instructions cannot be mixed. The CC file\n"
		"must be provided from the standard input. The result is printed to the standard\n"
		"output.\n"
		"\n"
		"List of valid instructions:\n"
		"   " PRINT_HELP                              "\n"
		"   " PRINT_HASH   " file-name"               "\n"
		"   " PRINT_FCOUNT                            "\n"
		"   " PRINT_TOC                               "\n"
		"   " PRINT_FNAME  " file-name (true|false)"  "\n"
		"   " PRINT_FID    " file-id   (true|false)"  "\n"
		"\n"
		PRINT_HELP "\n"
		"   Print usage instructions.\n"
		PRINT_HASH "\n"
		"   Print the hash for the file name provided as an argument.\n"
		PRINT_FCOUNT "\n"
		"   Print the file count of the CC file.\n"
		PRINT_TOC "\n"
		"   Print the table of contents of the CC file.\n"
		PRINT_FNAME "\n"
		"   Print the contents of the file provided by the file name. You must specify\n"
		"   whether the file is encrypted as \"true\" or \"false\".\n"
		PRINT_FID "\n"
		"   Print the contents of the file provided by the file id. You must specify\n"
		"   whether the file is encrypted as \"true\" or \"false\".\n"
	);
}

int atoh16(char *a, uint16_t *h) {
	ReturnCode error = SUCCESS;

	uint16_t hex = 0x0000;

	if (a[0] != 0 || a[1] != 'x' || a[1] != 'X') {
		fprintf(stderr, "Error: hexadecimal numbers must start with '0x' or '0X'.\n");
		error = ARGS;
		goto end;
	}
	a += 2;

	int chars = 0;
	while (*a != '\0' && chars < 4) {
		if (*a >= '0' && *a <= '9') {
			hex += *a - '0';
		} else if (*a >= 'A' && *a <= 'F') {
			hex += 10 + *a - 'A';
		} else if (*a >= 'a' && *a <= 'f') {
			hex += 10 + *a - 'a';
		} else {
			fprintf(stderr, "Error: hexadecimal numbers may not contain character %c.\n", *a);
			error = ARGS;
			goto end;
		}
		hex <<= 4;
		++chars;
	}

	*h = hex;
end:
	return error;
}

