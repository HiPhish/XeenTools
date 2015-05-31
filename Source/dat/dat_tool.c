#include <assert.h>
#include <stdlib.h>
#include "dat_tool.h"

#define XEEN_MAP_WIDTH   16
#define XEEN_MAP_HEIGHT  16


int xeen_map_size[XEEN_COORDS] = {
	[XEEN_X] = XEEN_MAP_WIDTH,
	[XEEN_Y] = XEEN_MAP_HEIGHT,
};

int xeen_read_sprite_info(FILE *fp, long o, int i, XeenSpriteFrameInfo *info) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		FREAD_FAIL,
	} error = SUCCESS;
	uint8_t bytes[3 * XEEN_SPRITE_DIRECTIONS];

	/* Preconditions */
	if (!fp || !info) {
		error = INVALID_ARGS;
		goto end;
	}

	/* Jump to position */
	if (fseek(fp, o + i*3*XEEN_SPRITE_DIRECTIONS, SEEK_SET) != 0) {
		error = FREAD_FAIL;
		goto end;
	}

	if (fread(bytes, sizeof(uint8_t), 12, fp) != 12 * sizeof(uint8_t)) {
		error = FREAD_FAIL;
		goto end;
	}

	*info = (XeenSpriteFrameInfo) {
		.first = {
			[XEEN_SPRITE_FRONT] = bytes[0 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_FRONT],
			[XEEN_SPRITE_LEFT ] = bytes[0 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_LEFT ],
			[XEEN_SPRITE_BACK ] = bytes[0 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_BACK ],
			[XEEN_SPRITE_RIGHT] = bytes[0 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_RIGHT],
		},
		.flip = {
			[XEEN_SPRITE_FRONT] = bytes[1 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_FRONT],
			[XEEN_SPRITE_LEFT ] = bytes[1 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_LEFT ],
			[XEEN_SPRITE_BACK ] = bytes[1 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_BACK ],
			[XEEN_SPRITE_RIGHT] = bytes[1 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_RIGHT],
		},
		.last = {
			[XEEN_SPRITE_FRONT] = bytes[2 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_FRONT],
			[XEEN_SPRITE_LEFT ] = bytes[2 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_LEFT ],
			[XEEN_SPRITE_BACK ] = bytes[2 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_BACK ],
			[XEEN_SPRITE_RIGHT] = bytes[2 * XEEN_SPRITE_DIRECTIONS + XEEN_SPRITE_RIGHT],
		},
	};

end:
	return error;
}

int xeen_read_outdoor_map(FILE *fp, XeenOutdoorMap *map) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		FREAD_FAIL,
		MALLOC_FAIL,
	} error = SUCCESS;

	/* Pre-conditions */
	if (!fp || !map) {
		return INVALID_ARGS;
		goto end;
	} else if (map->tile) {
		error = INVALID_ARGS;
		goto end;
	}

	XeenOutdoorTile *tile = NULL;

	/* Jump to position */
	if (fseek(fp, 0, SEEK_SET) != 0) {
		error = FREAD_FAIL;
		goto end;
	}

	#define TILES  (XEEN_MAP_WIDTH * XEEN_MAP_HEIGHT)
	uint8_t bytes[3 * TILES + 64];

	if (fread(bytes, sizeof(uint8_t), 3 * TILES, fp) != 3 * TILES * sizeof(uint8_t)) {
		error = FREAD_FAIL;
		goto end;
	}

	if (!(tile = malloc(TILES * sizeof(*tile)))) {
		error = MALLOC_FAIL;
		goto end;
	}

	for (int y = 0; y < XEEN_MAP_HEIGHT; ++y) {
		for (int x = 0; x < XEEN_MAP_WIDTH; ++x) {
			int i = 1 * y * XEEN_MAP_HEIGHT + 1 * x; /* Index of the tile.    */
			int j = 2 * y * XEEN_MAP_HEIGHT + 2 * x; /* Index into the bytes. */

			/* Wall data */
			tile[i].ground  = bytes[j + 0] & 0x0F; /* Low  nibble of low  byte. */
			tile[i].middle  = bytes[j + 0] & 0xF0; /* High nibble of low  byte. */
			tile[i].top     = bytes[j + 1] & 0x0F; /* Low  nibble of high byte. */
			tile[i].overlay = bytes[j + 1] & 0xF0; /* High nibble of high byte. */
			assert((tile[i]).ground < 16);

			/* Flags */
			tile[i].flags = bytes[2 * TILES + i];
		}
	}

	*map = (XeenOutdoorMap) {
		.tile = tile,

		/* Skip two bytes because they possibly incorrect and not needed */

		#define OFF(n)  (3 * TILES + n)
		.map_n = bytes[OFF(2)],
		.map_e = bytes[OFF(3)],
		.map_s = bytes[OFF(4)],
		.map_w = bytes[OFF(5)],

		.maze_flag_1 = ((uint16_t)bytes[OFF(7)] << 8) + (uint16_t)bytes[OFF(6)],
		.maze_flag_2 = ((uint16_t)bytes[OFF(9)] << 8) + (uint16_t)bytes[OFF(8)],

		.wall_types = {
			[ 0] = bytes[OFF(10) +  0],
			[ 1] = bytes[OFF(10) +  1],
			[ 2] = bytes[OFF(10) +  2],
			[ 3] = bytes[OFF(10) +  3],
			[ 4] = bytes[OFF(10) +  4],
			[ 5] = bytes[OFF(10) +  5],
			[ 6] = bytes[OFF(10) +  6],
			[ 7] = bytes[OFF(10) +  7],
			[ 8] = bytes[OFF(10) +  8],
			[ 9] = bytes[OFF(10) +  9],
			[10] = bytes[OFF(10) + 10],
			[11] = bytes[OFF(10) + 11],
			[12] = bytes[OFF(10) + 12],
			[13] = bytes[OFF(10) + 13],
			[14] = bytes[OFF(10) + 14],
			[15] = bytes[OFF(10) + 15],
		},

		.floor_types = {
			[ 0] = bytes[OFF(26) +  0],
			[ 1] = bytes[OFF(26) +  1],
			[ 2] = bytes[OFF(26) +  2],
			[ 3] = bytes[OFF(26) +  3],
			[ 4] = bytes[OFF(26) +  4],
			[ 5] = bytes[OFF(26) +  5],
			[ 6] = bytes[OFF(26) +  6],
			[ 7] = bytes[OFF(26) +  7],
			[ 8] = bytes[OFF(26) +  8],
			[ 9] = bytes[OFF(26) +  9],
			[10] = bytes[OFF(26) + 10],
			[11] = bytes[OFF(26) + 11],
			[12] = bytes[OFF(26) + 12],
			[13] = bytes[OFF(26) + 13],
			[14] = bytes[OFF(26) + 14],
			[15] = bytes[OFF(26) + 15],
		},

		.floor_type   = bytes[OFF(42)],
		.run_x        = bytes[OFF(43)],
		.wall_no_pass = bytes[OFF(44)],
		.surf_no_pass = bytes[OFF(45)],
		.unlock_door  = bytes[OFF(46)],
		.unlock_box   = bytes[OFF(47)],
		.bash_door    = bytes[OFF(48)],
		.bash_grate   = bytes[OFF(49)],
		.bash_wall    = bytes[OFF(50)],
		.run_chance   = bytes[OFF(51)],
		.run_y        = bytes[OFF(52)],
		.trap_dmg     = bytes[OFF(53)],
		.wall_type    = bytes[OFF(54)],
		.tavern_tips  = bytes[OFF(55)],

		.seen = ((uint32_t)bytes[OFF(59)] << 24) +((uint32_t)bytes[OFF(58)] << 16)
		      + ((uint32_t)bytes[OFF(57)] <<  8) +((uint32_t)bytes[OFF(56)] <<  0),

		.stepped = ((uint32_t)bytes[OFF(63)] << 24) +((uint32_t)bytes[OFF(62)] << 16)
		         + ((uint32_t)bytes[OFF(61)] <<  8) +((uint32_t)bytes[OFF(60)] <<  0),
		#undef OFF
	};
	#undef TILES

end:
	return error;
}

