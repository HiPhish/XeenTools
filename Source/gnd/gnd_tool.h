#ifndef XEEN_GND_TOOL_H
#define XEEN_GND_TOOL_H

/** @file gnd_tool.h
 *
 *  Interface for GND sprite files.
 *
 *  GND files always contain one frame for the ground with a fixed size.
 */

/** All the possible GND frames. */
enum xeen_gnd_frame {
	XEEN_GND_FRAME,  /**< The only GND frame.   */
	XEEN_GND_FRAMES, /**< Number of GND frames. */
};

extern int xeen_gnd_size[XEEN_GND_FRAMES][2];

#endif /* XEEN_GND_TOOL_H */

