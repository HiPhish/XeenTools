#ifndef XEEN_MAZE_TOOL_H
#define XEEN_MAZE_TOOL_H

/** @file maze_tool.h
 *
 *  Interface for maze DAT files.
 *
 *  The "MAZExxxx.DAT" files that store maze layout for indoor- and outdoor
 *  mazes. The "MAZExxxx.MOB" file stores the objects, monsters and wall decors
 *  of the maze.
 *
 *  A "maze" is what is usually referred to as a map and the size of every maze
 *  is hard-coded to 16 x 16 tiles. If a maze is larger than that it means that
 *  it is actually made of several mazes stitched together. That's why every
 *  maze stores the IDs of up to four adjacent mazes.
 *
 *  The name of a maze file pair (DAT and MOB) is "MAZExxxx" where "xxxx" is
 *  the ID of the maze. If the ID is less than 100 the two leading characters
 *  are 0s. On the other hand, if the ID is greater than 99 the leading
 *  character is the letter "X".
 *
 *  The DAT and MOB files have no graphic informations, you have to load the
 *  corresponding sprite files yourself.
 */

#include <stdint.h>
#include <stdio.h>

#include "../xeen/xeen.h"

/** Structure of a maze tile.
 *
 *  The four layers have different meaning depending on whether it is an
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
 *
 *  The object, monster and decor are indices into the maze's corresponding
 *  arrays. The numbers have no meaning on their own.
 */
typedef struct xeen_maze_tile {
	/* --From DAT file-- */

	uint8_t layer[4] ; /**< Tiles or walls.             */
	uint8_t flags    ; /**< Tile flags.                 */
	uint8_t seen     ; /**< Tile has been "seen".       */
	uint8_t stepped  ; /**< Tile has been "stepped on". */

	/* --From MOB file-- */

	/** Object on the tile. */
	struct {
		uint8_t id;  /**< Index into the object array.    */
		uint8_t dir; /**< Direction the object is facing. */
	} object;

	/** Monster on the tile. */
	struct {
		uint8_t id;  /**< Index into the monster array.    */
		uint8_t dir; /**< Direction the monster is facing. */
	} monster;

	/** Ornament on the wall. */
	uint8_t decor; /**< Index into the decor array. */
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

/** Read a maze from from DAT and MOB file.
 *
 *  @param dat   File pointer to MAZExxxx.DAT.
 *  @param mob   File pointer to MAZExxxx.MOB.
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
 */
int xeen_read_maze(FILE *dat, FILE *mob, XeenMaze *maze);

#endif /* XEEN_MAZE_TOOL_H */

