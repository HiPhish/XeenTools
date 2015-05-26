#ifndef XEEN_PAL_TOOL_H
#define XEEN_PAL_TOOL_H

/** @file pal_tool.h
 *
 *  Interface for palette files.
 *
 *  A palette in *World of Xeen* is a linear array of RGB colours. The length
 *  of the array is hardcoded and the same for all palette files. On the
 *  original hardware it was possible to feed the file contents directly into
 *  the graphics adapter.
 *
 *  The colour format is 6-bit RGB, meaning every colour component uses six
 *  bytes, and is therefore restricted to a value between including 0 to
 *  including 63. The colour structure reflects this.
 */

#include <stdint.h>
#include <stdio.h>

/** Size of the palette in colours (byte triplets). */
#define XEEN_PAL_SIZE  256

/** Maximum value a colour component can have. */
#define XEEN_COLOR_MAX  0x3F

/** Structure of a raw Xeen colour. */
typedef struct xeen_color {
	uint8_t r; /**< Red   */
	uint8_t g; /**< Green */
	uint8_t b; /**< Blue  */
} XeenColor;

/** Retrieve the PAL-formatted palette from PAL file.
 *
 *  @param palette  Palette file.
 *  @param fo       Offset into the file to the palette.
 *  @param pal      Array for PAL colours.
 *
 *  @return  Error code:
 *             - 0: success
 *             - 1: Invalid arguments (see preconditions)
 *             - 2: Failed to allocate memory
 *             - 3: Failed reading file
 *
 *  @pre  The file must be readable.
 *  @pre  The pointer `pal` must be valid and pointing to a NULL-pointer.
 *
 *  @post  The memory pointed to by `*pal` will be allocated to a size of
 *         `XEEN_PAL_SIZE` and valid.
 */
int xeen_read_pal(FILE *fp, long fo, XeenColor **pal);

#endif /* XEEN_PAL_TOOL_H */

