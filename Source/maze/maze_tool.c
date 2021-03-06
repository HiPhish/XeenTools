#include <assert.h>
#include <stdlib.h>
#include "maze_tool.h"

#define MAZE_WIDTH   16
#define MAZE_HEIGHT  16

int xeen_maze_size[XEEN_COORDS] = {
	[XEEN_X] = MAZE_WIDTH,
	[XEEN_Y] = MAZE_HEIGHT,
};

int xeen_read_maze(FILE *dat, FILE *mob, XeenMaze *maze) {
	#define TILES  (MAZE_WIDTH * MAZE_HEIGHT)

	enum {
		SUCCESS,
		INVALID_ARGS,
		FREAD_FAIL,
		MALLOC_FAIL,
	} error = SUCCESS;

	XeenMazeTile *tile = NULL;

	/* Variables */
	uint8_t object_list  [16];
	uint8_t monster_list [16];
	uint8_t decor_list   [16];

	int mob_objects  = 0;
	int mob_monsters = 0;
	int mob_decors   = 0;

	uint8_t (*mob_object )[4] = NULL;
	uint8_t (*mob_monster)[4] = NULL;
	uint8_t (*mob_decor  )[4] = NULL;

	/* Pre-conditions */
	if (!dat || !mob || !maze) {
		error = INVALID_ARGS;
		goto fail;
	} else if (maze->tile) {
		error = INVALID_ARGS;
		goto fail;
	}

	/* Allocate memory for tiles */
	if (!(tile = malloc(TILES * sizeof(*tile)))) {
		error = MALLOC_FAIL;
		goto fail;
	}


	/*---------- DAT file ----------*/

	/* Rewind DAT file */
	if (fseek(dat, 0, SEEK_SET) != 0) {
		error = FREAD_FAIL;
		goto fail;
	}

	/* Raw bytes from the DAT file. */
	uint8_t dat_bytes[3 * TILES + 124];

	/* Read the DAT bytes into the array. */
	if (fread(dat_bytes, sizeof(dat_bytes[0]), 3 * TILES, dat) != sizeof(dat_bytes)) {
		error = FREAD_FAIL;
		goto fail;
	}

	/* Assign the tile data itself */
	for (int y = 0; y < MAZE_HEIGHT; ++y) {
		for (int x = 0; x < MAZE_WIDTH; ++x) {
			int i = 1 * y * MAZE_HEIGHT + 1 * x; /* Index of the tile.    */
			int j = 2 * y * MAZE_HEIGHT + 2 * x; /* Index into the bytes. */

			/* Wall data */
			tile[i].layer[0] = dat_bytes[j + 0] & 0x0F; /* Low  nibble of low  byte. */
			tile[i].layer[1] = dat_bytes[j + 0] & 0xF0; /* High nibble of low  byte. */
			tile[i].layer[2] = dat_bytes[j + 1] & 0x0F; /* Low  nibble of high byte. */
			tile[i].layer[3] = dat_bytes[j + 1] & 0xF0; /* High nibble of high byte. */

			/* Flags */
			tile[i].flags = dat_bytes[2 * TILES + i];
		}
	}


	/* Seen and stepped are near the end of the DAT file */
	do {
		int i = 3 * TILES + 60; /* Current byte */
		int b =              0; /* Current bit  */
		uint8_t mask = 0x01;

		for (int y = 0; y < MAZE_HEIGHT; ++y) {
			for (int x = 0; x < MAZE_WIDTH; ++x) {
				/* Current tile */
				int t = 1 * y * MAZE_HEIGHT + 1 * x;

				/* If we have read eight bits */
				if (b == 8) {
					++i;         /* Move to next byte */
					b    = 0;    /* Reset bit         */
					mask = 0x01; /* Reset mask        */
				}

				tile[t].seen    = dat_bytes[i+ 0] & mask ? 0x01 : 0x00;
				tile[t].stepped = dat_bytes[i+32] & mask ? 0x01 : 0x00;
				/* Next bit */
				++b;
				mask <<= 1;
			}
		}
	} while(0);

	
	/*---------- MOB file ----------*/

	#define READ_LIST(list) \
		if (fread(list, sizeof(list[0]), 16, mob) != sizeof(list)) { \
			error = FREAD_FAIL; \
			goto fail; \
		}
	READ_LIST( object_list  )
	READ_LIST( monster_list )
	READ_LIST( decor_list   )
	#undef READ_LIST

	/* Count the length of the three arrays */
	uint8_t mob_bytes[4] = {0x00, 0x00, 0x00, 0x00};
	#define COUNT_ITEMS(kind, count) \
		do { \
			if (fread(mob_bytes, sizeof(mob_bytes[0]), 4, mob) != sizeof(mob_bytes)) { \
				error = FREAD_FAIL; \
				goto fail; \
			} \
			++count; \
		} while (mob_bytes != (uint8_t[4]) {0xFF, 0xFF, 0xFF, 0xFF}); \
		if (fseek(mob, -(--count), SEEK_CUR)) { \
			error = FREAD_FAIL; \
			goto fail; \
		} \
		if (malloc(count * sizeof(*kind)) == NULL) { \
			error = MALLOC_FAIL; \
			goto fail; \
		} \
		if (fread(kind, sizeof(*kind), count, mob) != count * sizeof(*kind)) { \
			error = FREAD_FAIL; \
			goto fail; \
		} \
		/* skip over the terminating bytes */ \
		if (fseek(mob, 1, SEEK_CUR)) { \
			error = FREAD_FAIL; \
			goto fail; \
		}
	COUNT_ITEMS( mob_object , mob_objects  )
	COUNT_ITEMS( mob_monster, mob_monsters )
	COUNT_ITEMS( mob_decor  , mob_decors   )
	#undef COUNT_ITEMS
	assert(mob_object && mob_monster && mob_decor);

	/* Place data from MOB file into the tiles */
	for (int i = 0; i < mob_objects; ++i) {
		int x = mob_object[i][0];
		int y = mob_object[i][1];
		tile[y * MAZE_WIDTH + x].object.id  = mob_object[i][2];
		tile[y * MAZE_WIDTH + x].object.dir = mob_object[i][3];
	}
	for (int i = 0; i < mob_monsters; ++i) {
		int x = mob_monster[i][0];
		int y = mob_monster[i][1];
		tile[y * MAZE_WIDTH + x].monster.id  = mob_monster[i][2];
		tile[y * MAZE_WIDTH + x].monster.dir = mob_monster[i][3];
	}
	for (int i = 0; i < mob_decors; ++i) {
		int x = mob_decor[i][0];
		int y = mob_decor[i][1];
		tile[y * MAZE_WIDTH + x].decor = mob_decor[i][2];
	}

	free(mob_object); free(mob_monster); free(mob_decor);
	assert(!mob_object && !mob_monster && !mob_decor);

	/*----- Assigning data -----*/

	*maze = (XeenMaze) {
		.tile = tile,

		/* Skip two bytes because they possibly incorrect and not needed */

		#define OFF(n)  (3 * TILES + n) /* (3*TILES) = bytes we have already read */
		.maze_n = dat_bytes[OFF(2)],
		.maze_e = dat_bytes[OFF(3)],
		.maze_s = dat_bytes[OFF(4)],
		.maze_w = dat_bytes[OFF(5)],

		.maze_flag_1 = ((uint16_t)dat_bytes[OFF(7)] << 8) + (uint16_t)dat_bytes[OFF(6)],
		.maze_flag_2 = ((uint16_t)dat_bytes[OFF(9)] << 8) + (uint16_t)dat_bytes[OFF(8)],

		.wall_types = {
			[ 0] = dat_bytes[OFF(10) +  0], [ 1] = dat_bytes[OFF(10) +  1],
			[ 2] = dat_bytes[OFF(10) +  2], [ 3] = dat_bytes[OFF(10) +  3],
			[ 4] = dat_bytes[OFF(10) +  4], [ 5] = dat_bytes[OFF(10) +  5],
			[ 6] = dat_bytes[OFF(10) +  6], [ 7] = dat_bytes[OFF(10) +  7],
			[ 8] = dat_bytes[OFF(10) +  8], [ 9] = dat_bytes[OFF(10) +  9],
			[10] = dat_bytes[OFF(10) + 10], [11] = dat_bytes[OFF(10) + 11],
			[12] = dat_bytes[OFF(10) + 12], [13] = dat_bytes[OFF(10) + 13],
			[14] = dat_bytes[OFF(10) + 14], [15] = dat_bytes[OFF(10) + 15],
		},

		.floor_types = {
			[ 0] = dat_bytes[OFF(26) +  0], [ 1] = dat_bytes[OFF(26) +  1],
			[ 2] = dat_bytes[OFF(26) +  2], [ 3] = dat_bytes[OFF(26) +  3],
			[ 4] = dat_bytes[OFF(26) +  4], [ 5] = dat_bytes[OFF(26) +  5],
			[ 6] = dat_bytes[OFF(26) +  6], [ 7] = dat_bytes[OFF(26) +  7],
			[ 8] = dat_bytes[OFF(26) +  8], [ 9] = dat_bytes[OFF(26) +  9],
			[10] = dat_bytes[OFF(26) + 10], [11] = dat_bytes[OFF(26) + 11],
			[12] = dat_bytes[OFF(26) + 12], [13] = dat_bytes[OFF(26) + 13],
			[14] = dat_bytes[OFF(26) + 14], [15] = dat_bytes[OFF(26) + 15],
		},

		.floor_type   = dat_bytes[OFF(42)],
		.run_x        = dat_bytes[OFF(43)],
		.wall_no_pass = dat_bytes[OFF(44)],
		.surf_no_pass = dat_bytes[OFF(45)],
		.unlock_door  = dat_bytes[OFF(46)],
		.unlock_box   = dat_bytes[OFF(47)],
		.bash_door    = dat_bytes[OFF(48)],
		.bash_grate   = dat_bytes[OFF(49)],
		.bash_wall    = dat_bytes[OFF(50)],
		.run_chance   = dat_bytes[OFF(51)],
		.run_y        = dat_bytes[OFF(52)],
		.trap_dmg     = dat_bytes[OFF(53)],
		.wall_type    = dat_bytes[OFF(54)],
		.tavern_tips  = dat_bytes[OFF(55)],
		#undef OFF
	};

	return error;

fail:
	if ( tile        ) {free( tile        );}
	if ( mob_object  ) {free( mob_object  );}
	if ( mob_monster ) {free( mob_monster );}
	if ( mob_decor   ) {free( mob_decor   );}
	return error;

	#undef TILES
}

