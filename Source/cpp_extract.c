#include <stdio.h>
#include <stdlib.h>
#include "cpp/cpp_tool.h"

void print_help();

int print_cpp(XeenCopyProtection cpp);

int main(int argc, char **argv) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		FREAD_FAIL,
	} error = SUCCESS;

	int index = 0;

	XeenCopyProtection cpp = {
		.page = 0,
		.line = 0,
		.word = 0,
		.string[0] = '\0',
	};

	if (argc != 2) {
		error = INVALID_ARGS;
		goto end;
	}

	index = (int)strtol(argv[1], (char **)NULL, 10);

	if (xeen_read_copy_protection(stdin, 0, index, &cpp)) {
		error = FREAD_FAIL;
		goto end;
	}

	print_cpp(cpp);

end:
	return error;
}

int print_cpp(XeenCopyProtection cpp) {
	enum {
		SUCCESS,
		INVALID_ARGS,
	} error = SUCCESS;

	if (cpp.string[XEEN_CPP_LENGTH - 1] != '\0') {
		error = INVALID_ARGS;
		goto end;
	}

	printf("Page: %i, line: %i, word: %i, string: %s\n", cpp.page, cpp.line, cpp.word, cpp.string);

end:
	return error;
}

