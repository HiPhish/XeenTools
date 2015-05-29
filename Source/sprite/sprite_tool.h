#ifndef XEEN_SPRITE_TOOL_H
#define XEEN_SPRITE_TOOL_H

/** @file sprite_tool.h
 *
 *  The sprite tool provides the functions necessary for working with sprite
 *  image files.
 *
 *  The interface here is a general one for any type of sprite file and does
 *  not provide any information on the amount of frames or any other details.
 *  There are more specific interfaces of particular file types. Think of this
 *  as a backend and the other interfaces as frontends.
 *
 *  A sprite file has the following structure: A header telling us how many
 *  frames and cells are in the sprite, followed by an array of cells and an
 *  array that maps cells to frames.
 *
 *  +-------------+---------------+---------------------------------------+
 *  | Name        | Type          | Description                           |
 *  +=============+===============+=======================================+
 *  | frame count | uint16        | Number of frames in this sprite file. |
 *  +-------------+---------------+---------------------------------------+
 *  | cell count  | uint16        | Number of frames in this sprite file. |
 *  +-------------+---------------+---------------------------------------+
 *  | frame map   | uint16[fc][2] | Assigns up to two cells to a frame.   |
 *  +-------------+---------------+---------------------------------------+
 *  | cells       | cell[cc]      | Assigns up to two cells to a frame.   |
 *  +-------------+---------------+---------------------------------------+
 *
 *  where `fc` is the frame count and `cc` is the cell count.
 *
 *  The image data is stored in so-called cells, up to two cells can be placed
 *  on top of each other to form a frame. The frame map lists for every frame
 *  the indices of two cells, where the second index can be the same as the
 *  first if that frame consists of only one cell.
 *
 *  This approach allows saving memory when only a small part of a frame needs
 *  to change.  In that case all the frames will use the same cell as the
 *  bottom layer and only swap out the top layer.
 *
 *  If two cells of a frame have different height the upper cell is shorter. In
 *  that case the cells need to line up at the top.
 *
 *  A cell itself has its own header immediately followed by the cell data.
 *  Here is the uncompressed structure:
 *
 *  +--------+-----------------------+--------------------+
 *  | Name   | Type                  | Description        |
 *  +========+=======================+====================+
 *  | width  | uint16                | Width of the cell  |
 *  +--------+-----------------------+--------------------+
 *  | height | uint16                | Height of the cell |
 *  +--------+-----------------------+--------------------+
 *  | pixels | uint8[width * height] | Pixel bytes        |
 *  +--------+-----------------------+--------------------+
 *
 *  The pixel bytes are just offsets into a palette, so you will need one to
 *  create coloured pixels.
 *
 *  A cell is really just a frame that can be combined with another cell into a
 *  new frame. As such cells and frames use the same structure in this library.
 *
 *  The transparency colour is not specified, so you will have to supply a
 *  transparency byte to the functions. The game seems to use magenta for that
 *  purpose. It depends on the palette file used.
 */

#include <stdio.h>
#include <stdint.h>

/** A frame (or cell) of a sprite animation. */
typedef struct sprt_frame {
	uint16_t  width;  /**< Width of the frame.  */
	uint16_t  height; /**< Height of the frame. */
	uint8_t  *pixels; /**< Raw pixel bytes.     */
} XeenFrame;

/** Decompressed sprite structure.
 *
 *  A sprite consists of a collection of *cells*. To form a frame one or two
 *  cells are placed on top or each other. The frame map lists the indices of
 *  the cells for every frame.
 *
 *  The structure also contains information on how many frames and cells the
 *  sprite is made of. These are also the sizes of the frame map- and cells
 *  arrays.
 *
 *  The frame map is a pointer to arrays of two 16-bit integers. The length of
 *  the array sequence can vary, but the length of an array in the sequence is
 *  always two numbers.
 */
typedef struct xeen_sprite {
	uint16_t   frames   ; /**< Number of frames.    */
	uint16_t   cells    ; /**< Number of cells.     */
	uint16_t  (*map)[2] ; /**< Map cells to frames. */
	XeenFrame  *cell    ; /** Uncompressed cells.   */
} XeenSprite;

/** Read a sprite from file.
 *
 *  @param fp           File pointer.
 *  @param fo           File offset to the sprite data.
 *  @param sp           Pointer to structure to hold the result.
 *  @param transparent  Index of the transparent colour
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments (see precondition)
 *             - 2: Memory allocation failed
 *             - 3: File reading failed
 *
 *  @pre  The file must be readable.
 *  @pre  The pointer `sp` must be valid.
 *
 *  @post  The memory pointed to by `sp` will be allocated to the size of a
 *         sprite and valid.
 */
int xeen_read_sprite(FILE *fp, long fo, XeenSprite *sp, uint8_t transparent);

/** Get a frame of animation from a sprite.
 *
 *  @param sprite       The sprite to get the frame from.
 *  @param frame        Pointer to store the resulting frame.
 *  @param index        Index of the frame.
 *  @param transparent  Index of the transparent colour
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments (see precondition)
 *             - 2: Memory allocation failed
 *
 *  @pre  The sprite's frame map and cells need to be valid.
 *  @pre  The `frame` pointer must be valid.
 *  @pre  The content of the `frame` pointer must be a frame of 0 width and
 *        height and a NULL pointer for pixels.
 *
 *  @post  The memory pointed at by `frame` will be a valid frame on success.
 *
 *  The size of the resulting frame will be the size of the bigger of the two
 *  cells. If a frame consists of only one cell the pixels of the cell will be
 *  copied so the frame and the cell can changed without affecting the other.
 *  For frames made of two cells a new pixel sequence is created anyway.
 */
int xeen_get_frame(XeenSprite sprite, XeenFrame *frame, uint16_t index, uint8_t transparent);

#endif /* XEEN_SPRITE_TOOL_H */

