#ifndef XEEN_FAC_TOOL_H
#define XEEN_FAC_TOOL_H

/** @file fac_tool.h
 *
 *  Interface for FAC sprite files.
 *
 *  These files contain sprites used for facial expressions. There are three
 *  types: for characters, for NPCs and for death portraits. All three files
 *  are just regular sprite files, the only difference is the number of frames
 *  per type.
 *
 *  The size of face frames is hard-coded to 32 x 32 pixels. Since pixels on
 *  old CRT screen during the DOS era did not have square pixels the portraits
 *  appeared at the correct aspect ratio.
 *
 *  TODO: The names of the face frames need to be chosen better.
 */

#include "../sprite/sprite_tool.h"

/** The width of a face frame. */
#define XEEN_FAC_WIDTH   32

/** The height of a face frame. */
#define XEEN_FAC_HEIGHT  32

/* TODO: These names need to be re-though. */

/** Possible facial expressions for character. */
enum xeen_char_face {
	NORMAL,
	POISONED,
	SICK,
	UNCONSCIOUS,
	INSANE,
	XEEN_CHAR_FACES,
};

/** Possible facial expressions for NPCs. */
enum xeen_npc_face {
	FACE_0,
	FACE_1,
	FACE_2,
	FACE_3,
	XEEN_NPC_FACES,
};

/** Possible dead portraits. */
enum xeen_dead_face {
	DEAD_0,
	DEAD_1,
	DEAD_2,
	XEEN_DEAD_FACES,
};

#endif /* XEEN_FAC_TOOL_H */

