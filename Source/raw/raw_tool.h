#ifndef XEEN_RAW_TOOL_H
#define XEEN_RAW_TOOL_H

/** @file raw_tool.h
 *
 *  Interface for RAW image files.
 *
 *  A RAW image file holds an uncompressed image of fixed size. The image
 *  information is a continuous sequence of bytes that serve as indices into a
 *  palette. The library will read the result into a sprite with only one cell
 *  and only one frame.
 */

#include <stdio.h>
#include "../xeen/xeen.h"
#include "../sprite/sprite_tool.h"

/** Size of a RAW image in pixels (hard-coded). */
extern uint16_t xeen_raw_size[XEEN_COORDS];

/** Read a raw image form file into a sprite.
 *
 *  @param fp   File to read from.
 *  @param o    Offset into the file.
 *  @param raw  Pointer to a sprite to save the result to.
 *
 *  @return Error code:
 *            - 0: Success
 *            - 1: Invalid arguments
 *            - 2: Memory allocation failure.
 *            - 3: File reading failure.
 *
 *  @pre The pointers must be valid.
 *  @pre The sprite passed must be empty.
 *
 *  @post If successful the sprite passed will contain the read image.
 */
int xeen_read_raw(FILE *fp, long o, XeenSprite *raw);

#endif /* XEEN_RAW_TOOL_H */

