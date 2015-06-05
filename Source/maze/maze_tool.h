#ifndef XEEN_MAZE_TOOL_H
#define XEEN_MAZE_TOOL_H

/** @file maze_tool.h
 *
 *  Interface for maze DAT files.
 *
 *  The "MAZExxxx.DAT" files that store map layout for indoor- and outdoor
 *  maps.
 */

#include <stdint.h>
#include <stdio.h>

#include "../xeen/xeen.h"

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
	/* From DAT file */
	uint8_t layer[4]; /***< Tiles or walls. */

	/**< Object on the tile. */
	struct {
		uint8_t id;
		uint8_t dir;
	} object;

	/**< Monster on the tile. */
	struct {
		uint8_t id;
		uint8_t dir;
	} monster;

	uint8_t decor; /**< Ornament on the wall. */

	uint8_t flags; /***< Tile flags.     */

	uint8_t seen;    /**< Tile has been "seen".       */
	uint8_t stepped; /**< Tile has been "stepped on". */

	/* From MOB file */
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

	/* From the MOB file */
	uint8_t object_list  [16]; /** Array ob object sprite IDs to place on this map. */
	uint8_t monster_list [16]; /** Array of monster IDs to place on this map.       */
	uint8_t wall_list    [16]; /** Array of wall sprite IDs to place on this map.   */
} XeenMap;

/** Structure of Xeen map objects. */
typedef struct xeen_map_objects {
	
	uint8_t object_list  [16];
	/** Array of monster IDs to place on this map. */
	uint8_t monster_list [16];
	/** Array of wall sprite IDs to place on this map. */
	uint8_t wall_list    [16];

	
	int objects  ; /**< Number of object types.  */
	int monsters ; /**< Number of monster types. */
	int walls    ; /**< Number of wall types.    */

	uint8_t (*object )[4]; /**< List of lookup IDs of objects.  */
	uint8_t (*monster)[4]; /**< List of lookup IDs of monsters. */
	uint8_t (*wall   )[4]; /**< List of lookup IDs of walls.    */
} XeenMapObjects;

/** Size of map (hard-coded). */
extern int xeen_map_size[XEEN_COORDS];

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
int xeen_read_map(FILE *dat, FILE *mob, XeenMap *map);

#endif /* XEEN_MAZE_TOOL_H */

