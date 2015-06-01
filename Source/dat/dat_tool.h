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

/** Structure of a map file.
 *
 *  The four fields have different meaning depending on whether it is an
 *  outdoor- or indoor tile. For outdoor they are the terrain features of the
 *  map stacked on top of other, for indoor they are the walls surrounding the
 *  tile.
 *
 *  +--------+---------+--------+
 *  | Number | Outdoor | Indoor |
 *  +========+=========+========+
 *  |      0 | Base    | North  |
 *  +--------+---------+--------+
 *  |      1 | Middle  | East   |
 *  +--------+---------+--------+
 *  |      2 | Top     | South  |
 *  +--------+---------+--------+
 *  |      3 | Overlay | West   |
 *  +--------+---------+--------+
 */
typedef struct xeen_map_tile {
	uint8_t field [4]; /***< Tiles or walls. */
	uint8_t flags    ; /***< Tile flags.     */
} XeenMapTile;

/** Structure of an indoor map. */
typedef struct xeen_map {
	XeenMapTile *tile; /**< Sequence of tiles, row-major. */

	uint16_t map_n; /**< ID of the map to the north. */
	uint16_t map_e; /**< ID of the map to the east.  */
	uint16_t map_s; /**< ID of the map to the south. */
	uint16_t map_w; /**< ID of the map to the west.  */

	uint16_t maze_flag_1; /**< First set of map flags.  */
	uint16_t maze_flag_2; /**< Second set of map flags. */

	uint8_t wall_types  [16]; /**< 16 byte array of wall types, used for indirect lookup.   */
	uint8_t floor_types [16]; /**< 16 byte array of surface types used for indirect lookup. */

	uint8_t wall_type;    /**< The type of walls, used in a lookup table.                     */
	uint8_t floor_type;   /**< The default floor type (lookup table, used by indoor maps).    */
	uint8_t run_chance;   /**< Difficulty of running from a fight.                            */
	uint8_t run_x;        /**< X coordinate party will land at if they run from a fight.      */
	uint8_t run_y;        /**< Y coordinate party will land at if they run from a fight.      */
	uint8_t wall_no_pass; /**< Wall values greater than or equal cannot be walked through.    */
	uint8_t surf_no_pass; /**< Surface values greater than or equal cannot be walked through. */
	uint8_t unlock_door;  /**< Difficulty of unlocking a door on this map.                    */
	uint8_t unlock_box;   /**< Difficulty of unlocking a chest on this map.                   */
	uint8_t bash_door;    /**< Difficulty of bashing through a door.                          */
	uint8_t bash_grate;   /**< Difficulty of bashing through a grate.                         */
	uint8_t bash_wall;    /**< Difficulty of bashing through a wall.                          */
	uint8_t trap_dmg;     /**< Level of damage the party will receive from traps on this map. */
	uint8_t tavern_tips;  /**< Lookup table for the text file used by the tavern, if any.     */

	uint32_t seen;    /**< 16 x 16 bit array indicating which tiles have been "seen".       */
	uint32_t stepped; /**< 16 x 16 bit array indicating which tiles have been "stepped on". */
} XeenMap;

/** Size of map (hard-coded). */
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

/** Read a map from from DAT file.
 *
 *  @param fp  File pointer.
 *  @param map  Pointer where to store the map.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments
 *             - 2: File read fail
 *             - 3: Memory allocation fail
 *
 *  @pre The pointers must be valid.
 *  @pre The contents of the map pointer must be empty.
 *
 *  @post On success the map will be valid.
 *
 */
int xeen_read_map(FILE *fp, XeenMap *map);

#endif /* XEEN_DAT_TOOL_H */

