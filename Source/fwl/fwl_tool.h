#ifndef XEEN_FWL_TOOL_H
#define XEEN_FWL_TOOL_H

/** @file fwl_tool.h
 *
 *  Interface for FWL front-facing wall sprite files.
 *
 *  FWL files are regular sprite files that are part of an environment set.
 *  Each file contains one sprite with several frames. There are four files per
 *  environment set and the name pattern is "FxxxxN.FWL" where "xxxx" is the
 *  signature of the environment set and "N" the number of the file.
 *
 *  Walls are drawn at four distances, the nearest being adjacent to the player
 *  and the farthest three tiles away. The first two tiles contain the adjacent
 *  tiles; we need two files because one file would be too small to hold that
 *  many sprites.  The third file contains the next two distances and the
 *  fourth file the remaining sprites.
 *
 *  All sprites are static, with the exception of the torch sprite, it uses
 *  five frames of animation. The first frame is given, the other four are the
 *  next four frames.
 *
 *  There is also one unknown wall type, it appears to be just a leftover and
 *  does not contain anything useful.
 */

/** Different types of walls. */
enum xeen_fwl_types {
	XEEN_FWL_STANDARD , /**< Standard wall.        */
	XEEN_FWL_TORCH    , /**< Animated torch.       */
	XEEN_FWL_NICHE    , /**< Niche in the wall.    */
	XEEN_FWL_UNKNOWN  , /**< Unknown purpose.      */
	XEEN_FWL_DOOR_C   , /**< Closed door.          */
	XEEN_FWL_DOOR_O   , /**< Opened door.          */
	XEEN_FWL_GRATE_C  , /**< Closed grate.         */
	XEEN_FWL_BASHED   , /**< Bashed wall.          */
	XEEN_FWL_LADDER_U , /**< Ladder/stairs up.     */
	XEEN_FWL_LADDER_D , /**< Ladder/stairs down.   */
	XEEN_FWL_SAVE_C   , /**< Closed save.          */
	XEEN_FWL_GRATE_O  , /**< Open grate.           */
	XEEN_FWL_SAVE_O   , /**< Open save.            */
	XEEN_FWL_POSTS    , /**< Posts/pillars.        */
	XEEN_FWL_TYPES    , /**< Number of wall types. */
};

/** Frames of the wall torch animation. */
#define XEEN_FWL_TORCH_FRAMES  5

/** The different files for every wall. */
enum xeen_fwl_file {
	XEEN_FWL_1     , /**< Nearest sprite.         */
	XEEN_FWL_2     , /**< Nearest sprite (again). */
	XEEN_FWL_3     , /**< Near sprite.            */
	XEEN_FWL_4     , /**< Far sprite.             */
	XEEN_FWL_FILES , /**< Number of sprite files. */
};

/** Each of the files ends in a different digit like *Fxxxx1.FWL*. */
extern char xeen_fwl_file_to_char[XEEN_FWL_FILES];

/** The different distance levels. */
enum xeen_fwl_distance {
	XEEN_FWL_NEXT      , /**< Standing next to the wall.      */
	XEEN_FWL_CLOSE     , /**< One tile away from the wall.    */
	XEEN_FWL_NEAR      , /**< Two tiles away from the wall.   */
	XEEN_FWL_FAR       , /**< Three tiles away from the wall. */
	XEEN_FWL_DISTANCES , /**< Number of possible distances.   */
};

/** Structure of a forward wall information.
 *
 *  A file with the number 0 means there is no file.
 */
typedef struct xeen_fwl_info {
	int file;  /**< Number of the sprite file. */
	int frame; /**< Frame of this wall type.   */
} XeenFwlInfo;

/** Table of FWL information (hard-coded). */
extern XeenFwlInfo xeen_fwl_table[XEEN_FWL_TYPES][XEEN_FWL_DISTANCES];

#endif /* XEEN_FWL_TOOL_H */

