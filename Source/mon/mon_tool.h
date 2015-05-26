#ifndef XEEN_MON_TOOL_H
#define XEEN_MON_TOOL_H

/** @file mon_tool.h
 *
 *  Interface for the MON sprite files.
 *
 *  A MON file is a sprite file with eight idle frames.
 */

#include "../sprite/sprite_tool.h"

/** Frames in an ATT files. */
enum xeen_mon_frame {
	XEEN_MON_0      , /**< First idle frame.  */
	XEEN_MON_1      , /**< Second idle frame. */
	XEEN_MON_2      , /**< Third idle frame.  */
	XEEN_MON_3      , /**< Third idle frame.  */
	XEEN_MON_4      , /**< Third idle frame.  */
	XEEN_MON_5      , /**< Third idle frame.  */
	XEEN_MON_6      , /**< Third idle frame.  */
	XEEN_MON_7      , /**< Third idle frame.  */
	XEEN_MON_FRAMES , /**< Number of MON frames. */
};

/** Get a frame from a MON file.
 *
 *  @param f      Index of the frame.
 *  @param s      Sprite of the MON file
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
 *  @pre The index must be within the range of MON frames.
 *
 *  @post On success the frame's pixel array will be allocated and valid.
 */
int xeen_mon_get_frame(enum xeen_mon_frame f, XeenSprite s, XeenFrame *frame, uint8_t t);

#endif /* XEEN_MON_TOOL_H */

