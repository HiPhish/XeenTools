#ifndef XEEN_FNT_TOOL_H
#define XEEN_FNT_TOOL_H

/** @file fnt_tool.h
 *
 *  Interface for FNT font files.
 *
 *  A font file is a file named simply *FNT*, without extension. All font files
 *  have the same size: the number of ASCII characters times two times times
 *  the number of lines per character times two bytes.
 *
 *  Let's break this down: for every ASCII character there are two glyphs, one
 *  regular sized and one smaller sized. Every glyph is made of eight
 *  horizontal lines and every line is made of two bytes. That's a total of
 *  4.096 bytes.
 *
 *  For every glyph there is also spacing information, always stored as one
 *  byte each.
 *
 *  The glyph array is therefore a three-dimensional array: The outer dimension
 *  is the ASCII character, the middle dimension the variant (large or small)
 *  and the inner array are the lines.
 *
 *  Every line is 16 bits large and every glyph pixel is stored as two bits,
 *  that's eight bits per line. Every pixel can have a value between 0 and 3,
 *  with 0 being transparent. That means a character can have three different
 *  colours. Lines are stored form left to right.
 *
 *  To decode the pixel of a line mask the two bits first and then push them to
 *  the right. In general, given a line and an index
 *  @code
 *      uint16_t l;
 *      int i; // i < XEEN_GLYPH_LINE_PIXELS
 *  @endcode
 *  we need a mask
 *  @code
 *      uint16_t mask = (0xC000 >> XEEN_GLYPH_PIXEL_SIZE * i)
 *  @code
 *  to get the two bits we want. Then we must right-shift the bits
 *  @code
 *     	uint8_t pixel = (l&mask) >> XEEN_GLYPH_PIXEL_SIZE*(XEEN_GLYPH_LINE_PIXELS-i-1);
 *  @endcode
 *  to get the pixel, as a byte in this case.
 *
 *  Aside from the glyphs themselves there is also spacing information stored
 *  in the FNT file. There is one byte for every glyph, indexed first by the
 *  character, second by the typeface.
 */

#include <stdint.h>
#include <stdio.h>

/** Number of characters stored in a FNT file */
#define XEEN_FNT_CHARS  128

/** Typefaces for a character */
enum xeen_typeface {
	XEEN_TYPE_LARGE, /**< Larger glyph typeface.  */
	XEEN_TYPE_SMALL, /**< Smaller glyph typeface. */
	XEEN_TYPEFACES , /**< Number of typefaces.    */
};

/** Lines per glyph. */
#define XEEN_GLYPH_LINES  8

/** Pixels per glyph line. */
#define XEEN_GLYPH_LINE_PIXELS  8

/** Size of a glyph pixels in bits (not bytes). */
#define XEEN_GLYPH_PIXEL_SIZE  2

/** Font structure. */
typedef struct xeen_font {
	uint16_t glyph[XEEN_FNT_CHARS][XEEN_TYPEFACES][XEEN_GLYPH_LINES]; /**< Glyphs.  */
	uint8_t  space[XEEN_FNT_CHARS][XEEN_TYPEFACES];                   /**< Spacing. */
} XeenFont;

/** Read the contents of a FNT file.
 *
 *  @param fp
 *  @param o
 *  @param fnt
 *
 *  @return Error code:
 *            - 0: Success
 *            - 1: Invalid arguments
 *            - 2: Failed reading file
 *
 *  @pre  The pointers must be valid.
 *
 *  @post  The font will be assigned.
 *
 *  This function will mutate the font even if it fails, so be careful when
 *  passing it a pointer.
 */
int xeen_read_font(FILE *fp, long o, XeenFont *fnt);

/** Initialise an empty font object.
 *
 *  This function just returns an empty font object where every member is zero.
 */
XeenFont xeen_fnt_init();

#endif /* XEEN_FNT_TOOL_H */

