#ifndef XEEN_SKY_TOOL_H
#define XEEN_SKY_TOOL_H

/** @file gnd_tool.h
 *
 *  Interface for SKY sprite files.
 *
 *  SKY files always contain two frames for the sky with a fixed size. The
 *  first frame is the sky above the party and is always drawn. The second
 *  frame is the rest of the sky if front of the party and can be omitted if
 *  the party is standing in front of a wall that is flanked by two wall
 *  segments with the same direction from both sides.
 *  @code
 *        walls
 *     --- --- ---
 *          |
 *        party
 *  @endcode
 */

/** All the possible SKY frames. */
enum xeen_sky_frames {
	XEEN_SKY_ABOVE,  /**< Sky above the party.       */
	XEEN_SKY_FRONT,  /**< Sky in front of the party. */
	XEEN_SKY_FRAMES, /**< Number of GND frames.      */
};

extern int xeen_sky_size[XEEN_SKY_FRAMES][2];

#endif /* XEEN_SKY_TOOL_H */

