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

/** Get a character face frame from a FAC file.
 *
 *  @param f      Index of the frame.
 *  @param s      Sprite of the FAC file
 *  @param frame  Where to store the resulting frame.
 *  @param t      Transparency index.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments
 *             - Otherwise error code of `xeen_get_frame` +2
 *
 *  @pre The sprite must have a valid frame map and cells array.
 *  @pre The frame pointer must be valid.
 *  @pre The frame pointer's pixel array must be invalid.
 *  @pre The index must be within the range of character FAC frames.
 *
 *  @post On success the frame's pixel array will be allocated and valid.
 *  @post The size of the frame will be the size of a face frame.
 */
int xeen_fac_char_get_frame(enum xeen_char_face f, XeenSprite s, XeenFrame *frame, uint8_t t);


/** Get an NPC face frame from a FAC file.
 *
 *  @param f      Index of the frame.
 *  @param s      Sprite of the FAC file
 *  @param frame  Where to store the resulting frame.
 *  @param t      Transparency index.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments
 *             - Otherwise error code of `xeen_get_frame` +2
 *
 *  @pre The sprite must have a valid frame map and cells array.
 *  @pre The frame pointer must be valid.
 *  @pre The frame pointer's pixel array must be invalid.
 *  @pre The index must be within the range of NPC FAC frames.
 *
 *  @post On success the frame's pixel array will be allocated and valid.
 *  @post The size of the frame will be the size of a face frame.
 */
int xeen_fac_npc_get_frame(enum xeen_npc_face f, XeenSprite s, XeenFrame *frame, uint8_t t);

/** Get a death face frame from a FAC file.
 *
 *  @param f      Index of the frame.
 *  @param s      Sprite of the FAC file
 *  @param frame  Where to store the resulting frame.
 *  @param t      Transparency index.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments
 *             - Otherwise error code of `xeen_get_frame` +2
 *
 *  @pre The sprite must have a valid frame map and cells array.
 *  @pre The frame pointer must be valid.
 *  @pre The frame pointer's pixel array must be invalid.
 *  @pre The index must be within the range of death FAC frames.
 *
 *  @post On success the frame's pixel array will be allocated and valid.
 *  @post The size of the frame will be the size of a face frame.
 */
int xeen_fac_dead_get_frame(enum xeen_dead_face f, XeenSprite s, XeenFrame *frame, uint8_t t);

#endif /* XEEN_FAC_TOOL_H */

