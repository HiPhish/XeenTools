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

#endif /* XEEN_MON_TOOL_H */

