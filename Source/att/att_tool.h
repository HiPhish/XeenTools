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

#endif /* XEEN_ATT_TOOL_H */

