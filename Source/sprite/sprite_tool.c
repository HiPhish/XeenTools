#include <stdlib.h>
#include <assert.h>
#include <string.h> /* memcpy */
#include "sprite_tool.h"

/** Check condition and go to fail if it fails. */
#define CHECK(lhs, rhs, n) if((lhs) != (rhs)) {error=(n);goto fail;}
#define ALLOC(lhs, size) if(!(lhs = malloc(size))) {error=(ALLOC_FAIL);goto fail;}

#define READ(to, size, amount) \
	CHECK(fread(to, size, amount * size, fp), (size) * (amount), FREAD_FAIL)

/** Flip bytes if necessary (because endianess) */
#define FLIP_BYTES(var, count) \
	for (int i = 0; i < (count); ++i) { \
		uint8_t *p = (uint8_t *)&(var[i]); \
		var[i] = (p[1] << 8) + (p[0] << 0); \
	}

/* This function is rather large because it must do several things at once.
 * First it reads the head of the sprite. Then the cell offsets are loaded.
 *
 * The problem is that we only know how many frames there are, but not how many
 * cells. Instead we will load all cell offsets and then loop over them. For
 * every cell offset that we have not already come across increment the number
 * of cells. This allows us the identify every cell by a unique index.
 *
 * The next part is actually decompressing the cells. This is the largest part
 * of the code, but it is straight-forward if you know the algorithm.
 *
 * The placing of pixels is down using a "canvas" and a "brush": the canvas is
 * a pointer to the start of the pixel sequence, while the brush is a pointer
 * that moves along the sequence. Using the canvas we always know where in
 * memory the sequence lies and the cell's other members tell us how large it
 * is. The brush provides us with flexibility to move across the sequence.
 *
 * Finally, if all steps worked without error we can assign the values to the
 * sprite structure. The cell offset sequence is no longer needed, so it can be
 * freed again.
 */
int xeen_read_sprite(FILE *fp, long fo, XeenSprite *sp, uint8_t transparent) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		NO_CELLS,
		ALLOC_FAIL,
		FREAD_FAIL,
	} error = SUCCESS;

	uint8_t word[2]; /* Read 16-bit integers into this first */

	uint16_t  frames       = 0; /* Number of frames in the sprite */
	uint16_t  cell_count   = 0; /* Number of cells in the sprite  */
	uint16_t *cell_offsets = NULL;

	XeenSpriteFrameMap *frame_map = NULL;

	/* Pointer to cell memory and current pixel. */
	uint8_t   *canvas = NULL, *brush = NULL;
	/* Store the decompressed cells here */
	XeenFrame *cells  = NULL;

	/* ==== Part I - Reading sprite header ==== */

	/* Rewind sprite file */
	fseek(fp, fo, SEEK_SET);

	READ(word, sizeof(uint8_t), 2)
	frames = ((uint16_t)word[1] << 8) + ((uint16_t)word[0] << 0);

	ALLOC(cell_offsets, 2 * frames * sizeof(uint16_t))
	ALLOC(frame_map   , frames * sizeof(*frame_map))

	/** ==== Part II - Cell offsets ==== */

	/* Read the naked bytes first */
	READ(cell_offsets, sizeof(uint8_t), 4 * frames);
	FLIP_BYTES(cell_offsets, 2 * frames)

	/* Loop over the frames */
	for (int i = 0; i < frames; ++i) {
		for (int j = 0; j < 2; ++j) {
			/* If the offset is 0x0000 it means no cell */
			if (cell_offsets[2*i+j] == 0x000) {
				/* this may only be the case for the second cell */
				assert(j == 1);
				frame_map[i].cell[j] = frame_map[i].cell[j-1];
				continue;
			}
			/* If the cell is known */
			int known_cell = 0;
			for (int k = 0; k < 2*i+j; ++k) {
				if (cell_offsets[k] == cell_offsets[2*i+j]) {
					known_cell = 1;
					frame_map[i].cell[j] = frame_map[k/2].cell[k%2];
					break;
				}
			}
			if (known_cell) {
				continue;
			}

			frame_map[i].cell[j] = cell_count++;
		}
	}
	/* Now all cells are accessible by index */

	if (cell_count == 0) {
		error = NO_CELLS;
		goto fail;
	}

	/* ==== Part III - Decompressing the cells ==== */

	/* The next step is to decompress the cells */
	ALLOC(cells, cell_count * sizeof(XeenFrame))
	/* Initialise all cells to empty */
	for (int i = 0; i < cell_count; ++i) {
		cells[i] = (XeenFrame) {
			.width = 0, .height = 0, .pixels = NULL
		};
	}

	/* Read the raw cell data using the offsets */
	for (int i = 0; i < cell_count; ++i) {
		#define OFFSET_X  h[0]
		#define WIDTH     h[1]
		#define OFFSET_Y  h[2]
		#define HEIGHT    h[3]

		uint16_t offset = 0x0000;
		/* Find the offset of this cell */
		for (int j = 0; j < frames * 2; ++j) {
			if (frame_map[j/2].cell[j%2] == i) {
				offset = cell_offsets[j];
				break;
			}
			assert(j != frames * 2 - 1);
		}
		assert(offset != 0x0000);

		fseek(fp, offset + fo, SEEK_SET);
		uint16_t h[4]; /* Header of the cell */
		READ(h, sizeof(uint8_t), 8)
		FLIP_BYTES(h, 4)

		cells[i].width  = OFFSET_X + WIDTH;
		cells[i].height = OFFSET_Y + HEIGHT;
		#undef WIDTH
		#undef HEIGHT

		#define SURFACE  (cells[i].width * cells[i].height)
		/* Allocate memory for the cell canvas */
		ALLOC(canvas, SURFACE * sizeof(uint8_t))

		/* Fill the cell canvas with transparency */
		for (int j = 0; j < SURFACE; ++j) {
			canvas[j] = transparent;
		}
		#undef SURFACE

		/* loop over the drawing opcodes */
		for (uint16_t pos_y = OFFSET_Y; pos_y < cells[i].height; ++pos_y) {

			uint16_t bytes = 0; /* Bytes read on this line so far */
			uint8_t  l[2];      /* Line header */

			/* Move the brush to the beginning of the line */
			brush = canvas + cells[i].width * pos_y;

			/* Read line header */
			READ(l, sizeof(uint8_t), 2)

			/* Draw line */
			if (l[0] > 0) {
				++bytes; /* The line length counts as well */
				/* Horizontal position on the line */
				/* Move brush to the first pixel */
				brush += l[1];

				/* While there are bytes to read for the line */
				while (bytes < l[0]) {
					uint8_t opcode, command, length;

					/* Read the opcode */
					READ(&opcode, sizeof(uint8_t), 1)
					++bytes;

					/* Extract command and length from the opcode */
					command = (opcode & 0xE0) >> 5; /* Three most-significant bits */
					length  = (opcode & 0x1F) >> 0; /* Five least-significant bits */

					switch (command) {
						case 0:
						case 1:
							/* Copy this many pixels to the canvas */
							#define AMOUNT  (opcode + 1)
							READ(brush, sizeof(uint8_t), AMOUNT)

							bytes += AMOUNT;
							brush += AMOUNT;
							#undef AMOUNT
							break;
						case 2: {
							uint8_t op;
							READ(&op, sizeof(uint8_t), 1)
							++bytes;
							for (int i = 0; i < length + 3; ++i) {
								*(brush++) = op;
							}
							break;
						}
						case 3: {
							uint16_t offset;
							READ(word, sizeof(uint8_t), 2)
							bytes += 2;
							offset = (word[1] << 8) + (word[0] << 0);
							/* Use negative offset in the file */
							fseek(fp, -(long)offset, SEEK_CUR);
							/* Copy this many bytes */
							#define AMOUNT  (length + 4)
							READ(brush, sizeof(uint8_t), AMOUNT)
							brush += AMOUNT;
							/* Move the file back to where it was */
							fseek(fp, (long)offset - AMOUNT, SEEK_CUR);
							#undef AMOUNT
							break;
						}
						case 4: {
							READ(word, sizeof(uint8_t), 2)
							bytes += 2;
							for (int i = 0; i < length + 2; ++i) {
								*(brush++) = word[0];
								*(brush++) = word[1];
							}
							break;
						}
						case 5:
							/* Skip these pixels */
							brush += length + 1;
							break;
						case 6:
						case 7: {
							const int patternSteps[] = {
								0,  1,  1,  1,  2,  2,  3,  3,
								0, -1, -1, -1, -2, -2, -3, -3
							};

							uint8_t key    = (opcode >> 2) & 0x0E;
							uint8_t count  = (opcode >> 0) & 0x07;
							uint8_t value;

							READ(&value, sizeof(uint8_t), 1)
							++bytes;
							for (int i = 0; i < count + 3; ++i) {
								*(brush++) = value;
								value += patternSteps[key + (i % 2)];
							}
							break;
						}
						default:
							assert(0);
					}
				}
			} else {
				/* Skip scan lines. */
				pos_y += l[1];
			}
		}
		#undef OFFSET_X
		#undef OFFSET_Y
		cells[i].pixels = canvas;
	}

	/* ==== Part IV - Putting it together */

	/* All the cells have been loaded */
	free(cell_offsets); cell_offsets = NULL;

	/* Now assign the sprite variables */
	*sp = (XeenSprite) {
		.frames     = frames,
		.cell_count = cell_count,
		.frame_map  = frame_map,
		.cell       = cells,
	};

	return error;

fail:
	if (cell_offsets) { free(cell_offsets); }
	if (frame_map   ) { free(frame_map   ); }
	if (cells       ) {
		for (int i = 0; i < cell_count; ++i) {
			if (cells[i].pixels) { free(cells[i].pixels); }
		}
		free(cells);
	}
	if (canvas      ) { free(canvas      ); }
	return error;
}

int xeen_get_frame(XeenSprite sprite, XeenFrame *frame, uint16_t index, uint8_t transparent) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		ALLOC_FAIL,
	} error  = SUCCESS;

	uint8_t *pixels = NULL; /* Array of pixel bytes. */

	/* Cell indices */
	int i[2] = {
		sprite.frame_map[index].cell[0], /**< Cell index 0. */
		sprite.frame_map[index].cell[1], /**< Cell index 1. */
	};

	/** Surface area of the cells in pixels. */
	int surface[2] = {
		sprite.cell[i[0]].width * sprite.cell[i[0]].height,
		sprite.cell[i[1]].width * sprite.cell[i[1]].height,
	};

	/* Pre-conditions */
	if (!sprite.cell || !sprite.frame_map || !frame) {
		error = INVALID_ARGS; /* Pointers must be valid. */
		goto fail;
	}
	if (frame->pixels != NULL || frame->width != 0 || frame->height != 0) {
		error = INVALID_ARGS; /* Frame must be initialised to empty. */
		goto fail;
	}

	/* Allocate memory for the sprite map */
	ALLOC(pixels, sizeof(uint8_t) * surface[0])

	/* Copy the first cell */
	memcpy(pixels, sprite.cell[i[0]].pixels, surface[0] * sizeof(uint8_t));

	/* If the frame is using only one cell */
	if (i[0] != i[1]) { 
		for (int j = 0; j < surface[1]; ++j) {
			if (sprite.cell[i[1]].pixels[j] == transparent) { continue; }
			pixels[j] = sprite.cell[i[1]].pixels[j];
		}
	}

	*frame = (XeenFrame) {
		.width  = sprite.cell[i[0]].width,
		.height = sprite.cell[i[0]].height,
		.pixels = pixels,
	};

	return error;

fail:
	if (pixels) { free(pixels); }
	return error;
}

