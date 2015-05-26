#ifndef XEEN_ATT_TOOL_H
#define XEEN_ATT_TOOL_H

/** @file att_tool.h
 *
 *  Interface for the ATT sprite files.
 *
 *  An ATT file is a sprite file with three attack frames and one hit frame for
 *  when the monster was hit.
 */

#include "../sprite/sprite_tool.h"

/* Frames in an ATT files. */
enum xeen_att_frame {
	XEEN_ATT_0      , /**< First attack frame.  */
	XEEN_ATT_1      , /**< Second attack frame. */
	XEEN_ATT_2      , /**< Third attack frame.  */
	XEEN_HIT        , /**< Hit frame.           */
	XEEN_ATT_FRAMES , /**< Number of ATT frames. */
};

/** Get a frame from an ATT file.
 *
 *  @param f      Index of the frame.
 *  @param s      Sprite of the ATT file
 *  @param frame  Where to store the resulting frame.
 *  @param t      Transparency index.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments
 *             - Otherwise error code of `xeen_get_frame` +1
 *
 *  @pre The sprite must have a valid frame map and cells array.
 *  @pre The frame pointer must be valid.
 *  @pre The frame pointer's pixel array must be invalid.
 *  @pre The index must be within the range of ATT frames.
 *
 *  @post On success the frame's pixel array will be allocated and valid.
 */
int xeen_att_get_frame(enum xeen_att_frame f, XeenSprite s, XeenFrame *frame, uint8_t t);

#endif /* XEEN_ATT_TOOL_H */

