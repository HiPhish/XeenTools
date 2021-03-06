#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "sprite/sprite_tool.h"
#include "pal/pal_tool.h"

/** Transparency colour of the MM4.PAL file. */
#define TRANSPARENT  (8*16+6)

/** Print usage instructions. */
void print_help();

void print_sprite_info(XeenSprite s);

/** Print a frame as a PPM file to the standard output.
 *
 *  @param f  Frame to print.
 *  @param p  Palette to use.
 */
int print_frame_as_ppm(XeenFrame f, XeenColor *p);

int main(int argc, char **argv) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		PAL_FILE,
		SPR_READ_FAIL,
		FRM_GET_FAIL,
		PAL_READ_FAIL,
	} error = SUCCESS;

	enum {NONE, CELL, FRAME, INFO} option = NONE;

	int   frame_number = 0;
	int   cell_number  = 0;
	char *pal_fname;
	FILE *pal_file;


	XeenSprite s = {
		.frames = 0,
		.cells  = 0,
		.map    = NULL,
		.cell   = NULL,
	};

	XeenFrame f = {
		.width  = 0,
		.height = 0,
		.pixels = NULL,
	};

	XeenColor *p = NULL;

	if (argc != 5 && argc != 2) {
		error = INVALID_ARGS;
		print_help();
		goto end;
	}

	for (int i = 1; i < argc; ++i) {
		if (strncmp(argv[i], "--info", 6) == 0) {
			if (argc != 2) {
				error = INVALID_ARGS;
				print_help();
				goto end;
			}
			option = INFO;
			continue;
		}
		if (strncmp(argv[i], "--pal", 5) == 0) {
			pal_fname = argv[++i];
			continue;
		} 
		if (strncmp(argv[i], "--cell", 6) == 0) {
			cell_number = (int)strtol(argv[++i], (char **)NULL, 10);
			option = CELL;
			continue;
		} 
		if (strncmp(argv[i], "--frame", 7) == 0) {
			frame_number = (int)strtol(argv[++i], (char **)NULL, 10);
			option = FRAME;
			continue;
		} 
		print_help();
		exit(INVALID_ARGS);
	}
	assert(option != NONE);

	if (option != INFO) {
		if (!pal_fname) {
			error = INVALID_ARGS;
			goto end;
		}

		if ((pal_file = fopen(pal_fname, "r")) == NULL) {
			error = PAL_FILE;
			goto end;
		}

		/* Read the palette */
		if (xeen_read_pal(pal_file, 0, &p)) {
			error = PAL_READ_FAIL;
			goto end;
		}
		assert(p);
	}

	/* Read the sprite */
	if (xeen_read_sprite(stdin, 0, &s, TRANSPARENT)) {
		error = SPR_READ_FAIL;
		goto end;
	}
	assert(s.cell && s.map);

	switch (option) {
		case FRAME:
			if (xeen_get_frame(s, &f, frame_number, TRANSPARENT)) {
				error = FRM_GET_FAIL;
				goto end;
			}
			assert(f.pixels);
			print_frame_as_ppm(f, p);
			break;
		case CELL:
			if (cell_number >= s.cells) {
				error = INVALID_ARGS;
				goto end;
			}
			f = s.cell[cell_number];
			assert(f.pixels);
			f = s.cell[cell_number];
			print_frame_as_ppm(f, p);
			break;
		case INFO:
			print_sprite_info(s);
			break;
		default:
			assert(0);
	}

end:
	if (s.map   ) { free(s.map   ); }
	if (s.cell  ) { free(s.cell  ); }
	if (f.pixels) { free(f.pixels); }
	if (p       ) { free(p       ); }
	return error;
}

int print_frame_as_ppm(XeenFrame f, XeenColor *p) {
	enum {
		SUCCESS,
		FWRITE_FAIL,
	} error = SUCCESS;

	/* Print PPM header */
	fprintf(stdout, "P6 %i %i 255\n", f.width, f.height);
	/* And now the data */
	for (int i = 0; i < f.width * f.height; ++i) {
		uint8_t bytes[3] = {
			(p[f.pixels[i]].r << 2) | 0x03,
			(p[f.pixels[i]].g << 2) | 0x03,
			(p[f.pixels[i]].b << 2) | 0x03,
		};
		if (fwrite(bytes, sizeof(uint8_t), 3, stdout) != 3) {
			error = FWRITE_FAIL;
			goto end;
		}
	}


end:
	return error;
}

void print_sprite_info(XeenSprite s) {
	printf("Cells: %i; frames: %i\n", s.cells, s.frames);
	for (int i = 0; i < s.cells; ++i) {
		printf("  Cell %i: %i x %i\n", i, s.cell[i].width, s.cell[i].height);
	}
	for (int i = 0; i < s.frames; ++i) {
		int cell[2] = {
			s.map[i][0], s.map[i][1]
		};
		int width  = s.cell[cell[0]].width  > s.cell[cell[1]].width  ? s.cell[cell[0]].width  : s.cell[cell[1]].width;
		int height = s.cell[cell[0]].height > s.cell[cell[1]].height ? s.cell[cell[0]].height : s.cell[cell[1]].height;
		printf("  Frame %i: %i x %i (%i , %i)\n", i, width, height, cell[0], cell[1]);
	}
	printf("\n");
}

void print_help() {
	printf("Usage: sprite_extract --pal palette ((--cell number) | (--frame number))\n");
	printf("       sprite_extract --info\n");
	printf("\n");
	printf("The program is run by passing a palette file as an argument, as well as either\n");
	printf("a cell or a frame to print. The sprite file is the standard input and the\n");
	printf("result is a PPM file printed to the standard output.\n");
}
