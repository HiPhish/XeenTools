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

/** Structure of a maze tile.
 *
 *  The four fields have different meaning depending on whether it is an
 *  outdoor- or indoor tile. For outdoor they are the terrain features of the
 *  maze stacked on top of other, for indoor they are the walls surrounding the
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
typedef struct xeen_maze_tile {
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
} XeenMazeTile;

/** Structure of an indoor maze. */
typedef struct xeen_maze {
	XeenMazeTile *tile; /**< Sequence of tiles, row-major. */

	uint16_t maze_n; /**< ID of the maze to the north. */
	uint16_t maze_e; /**< ID of the maze to the east.  */
	uint16_t maze_s; /**< ID of the maze to the south. */
	uint16_t maze_w; /**< ID of the maze to the west.  */

	uint16_t maze_flag_1; /**< First set of maze flags.  */
	uint16_t maze_flag_2; /**< Second set of maze flags. */

	uint8_t wall_types  [16]; /**< 16 byte array of wall types, used for indirect lookup.   */
	uint8_t floor_types [16]; /**< 16 byte array of surface types used for indirect lookup. */

	uint8_t wall_type;    /**< The type of walls, used in a lookup table.                      */
	uint8_t floor_type;   /**< The default floor type (lookup table, used by indoor mazes).    */
	uint8_t run_chance;   /**< Difficulty of running from a fight.                             */
	uint8_t run_x;        /**< X coordinate party will land at if they run from a fight.       */
	uint8_t run_y;        /**< Y coordinate party will land at if they run from a fight.       */
	uint8_t wall_no_pass; /**< Wall values greater than or equal cannot be walked through.     */
	uint8_t surf_no_pass; /**< Surface values greater than or equal cannot be walked through.  */
	uint8_t unlock_door;  /**< Difficulty of unlocking a door on this maze.                    */
	uint8_t unlock_box;   /**< Difficulty of unlocking a chest on this maze.                   */
	uint8_t bash_door;    /**< Difficulty of bashing through a door.                           */
	uint8_t bash_grate;   /**< Difficulty of bashing through a grate.                          */
	uint8_t bash_wall;    /**< Difficulty of bashing through a wall.                           */
	uint8_t trap_dmg;     /**< Level of damage the party will receive from traps on this maze. */
	uint8_t tavern_tips;  /**< Lookup table for the text file used by the tavern, if any.      */

	/* From the MOB file */
	uint8_t object_list  [16]; /** Array ob object sprite IDs to place on this maze. */
	uint8_t monster_list [16]; /** Array of monster IDs to place on this maze.       */
	uint8_t wall_list    [16]; /** Array of wall sprite IDs to place on this maze.   */
} XeenMaze;

/** Size of maze (hard-coded). */
extern int xeen_maze_size[XEEN_COORDS];

/** Read a maze from from DAT file.
 *
 *  @param fp  File pointer.
 *  @param maze  Pointer where to store the maze.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments
 *             - 2: File read fail
 *             - 3: Memory allocation fail
 *
 *  @pre The pointers must be valid.
 *  @pre The contents of the maze pointer must be empty.
 *
 *  @post On success the maze will be valid.
 *
 */
int xeen_read_maze(FILE *dat, FILE *mob, XeenMaze *maze);

#endif /* XEEN_MAZE_TOOL_H */

