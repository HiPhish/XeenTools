#ifndef XEEN_DAT_TOOL_H
#define XEEN_DAT_TOOL_H

/** @file dat_tool.h
 *
 *  Interface for DAT files.
 *
 *  There are two kind of DAT files: One is called "CLOUDS.DAT" or "DARK.DAT"
 *  and contains sprite information on what sprite of an object to display for
 *  which direction. The other type as the "MAZExxxx.DAT" files that store map
 *  layout.
 *
 *  For sprites there are four directions, all relative to given relative to
 *  the player.  Every sprite information consists of the index of the first
 *  frame, whether the sprite is flipped horizontally and the index of the last
 *  frame.  Flipping allows the reuse of frames, for example when viewing an
 *  object from the left of the right.
 */

#include <stdint.h>
#include <stdio.h>

#include "../xeen/xeen.h"

/** Number of objects described in a DAT file. */
#define XEEN_DAT_OBJECTS  121

/* Possible directions a sprite can be facing. */
enum {
	XEEN_SPRITE_FRONT ,     /**< Facing the player.             */
	XEEN_SPRITE_LEFT  ,     /**< Player faces left side.        */
	XEEN_SPRITE_BACK  ,     /**< Facing away from the player.   */
	XEEN_SPRITE_RIGHT ,     /**< Player faces right side.       */
	XEEN_SPRITE_DIRECTIONS, /**< Number of possible directions. */
};

/** Information about a sprite's frames. */
typedef struct xeen_sprite_frame_info {
	uint8_t first [XEEN_SPRITE_DIRECTIONS]; /**< First frame.                  */
	uint8_t flip  [XEEN_SPRITE_DIRECTIONS]; /**< Whether to flip horizontally. */
	uint8_t last  [XEEN_SPRITE_DIRECTIONS]; /**< Last frame.                   */
} XeenSpriteFrameInfo;

enum xeen_outdoor_flag {
	XEEN_OUTDOOR_F_MON_L  = 0X01,
	XEEN_OUTDOOR_F_MON_C  = 0X02,
	XEEN_OUTDOOR_F_MON_R  = 0X04,
	XEEN_OUTDOOR_F_OBJECT = 0x08,
	XEEN_OUTDOOR_F_EVENT  = 0x10,
	XEEN_OUTDOOR_F_DRAIN  = 0x20,
	XEEN_OUTDOOR_F_WATER  = 0x40,
	XEEN_OUTDOOR_F_GRATE  = 0x80,
	XEEN_OUTDOOR_FLAGS    =    8,
};

enum xeen_indoor_flag {
	XEEN_INDOOR_F_INSIDE   = 0x08,
	XEEN_INDOOR_F_EVENT    = 0x10,
	XEEN_INDOOR_F_UNKOWN_2 = 0X20,
	XEEN_INDOOR_F_WATER    = 0x40,
	XEEN_INDOOR_F_UNKOWN_1 = 0X80,
	XEEN_INDOOR_FLAGS      =    5,
};

typedef struct xeen_outdoor_tile {
	uint8_t ground;
	uint8_t middle;
	uint8_t top;
	uint8_t overlay;
	uint8_t flags;
} XeenOutdoorTile;

typedef struct xeen_outdoor_map {
	XeenOutdoorTile *tile;

	uint16_t map_n;
	uint16_t map_e;
	uint16_t map_s;
	uint16_t map_w;

	uint16_t maze_flag_1;
	uint16_t maze_flag_2;

	uint8_t wall_types  [16];
	uint8_t floor_types [16];

	uint8_t wall_type;
	uint8_t floor_type;
	uint8_t run_chance;
	uint8_t run_x;
	uint8_t run_y;
	uint8_t wall_no_pass;
	uint8_t surf_no_pass;
	uint8_t unlock_door;
	uint8_t unlock_box;
	uint8_t bash_door;
	uint8_t bash_grate;
	uint8_t bash_wall;
	uint8_t trap_dmg;
	uint8_t tavern_tips;

	uint32_t seen;
	uint32_t stepped;
} XeenOutdoorMap;

typedef struct xeen_indoor_tile {
	uint8_t wall_n;
	uint8_t wall_e;
	uint8_t wall_s;
	uint8_t wall_w;
	uint8_t flags;
} XeenIndoorTile;

extern int xeen_map_size[XEEN_COORDS];

/** Read sprite information form a DAT file.
 *
 *  @param fp    File pointer.
 *  @param o     Offset to the sprite info data.
 *  @param i     Index of the sprite.
 *  @param info  Pointer to sprite info structure.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments
 *             - 2: File reading error.
 *
 *  @pre  File- and info pointer must be valid.
 *
 *  @post  The info pointer will contain the result.
 */
int xeen_read_sprite_info(FILE *fp, long o, int i, XeenSpriteFrameInfo *info);

int xeen_read_outdoor_map(FILE *fp, long o, XeenOutdoorMap *map);

#endif /* XEEN_DAT_TOOL_H */

