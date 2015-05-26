#ifndef XEEN_DAT_TOOL_H
#define XEEN_DAT_TOOL_H

/** @file dat_tool.h
 *
 *  Interface for DAT files.
 *
 *  A DAT file contains sprite information on what sprite of an object to
 *  display for direction. There are four directions, all relative to given
 *  relative to the player.
 *
 *  Every information consists of the index of the first frame, whether the
 *  sprite is flipped horizontally and the index of the last frame. Flipping
 *  allows the reuse of frames, for example when viewing an object from the
 *  left of the right.
 */

#include <stdint.h>
#include <stdio.h>

/** Number of objects described in a DAT file. */
#define XEEN_DAT_OBJECTS  121

/* Possible directions a sprite can be facing. */
enum {
	XEEN_SPRITE_FRONT ,     /**< Facing the player.             */
	XEEN_SPRITE_LEFT  ,     /**< Player faces left side.        */
	XEEN_SPRITE_BACK  ,     /**< Facing away from the player.   */
	XEEN_SPRITE_RIGHT ,     /**< Player faces right side.       */
	XEEN_SPRITE_DIRECTIONS, /**< Number of possible directions. */
};

/** Information about a sprite's frames. */
typedef struct xeen_sprite_frame_info {
	uint8_t first [XEEN_SPRITE_DIRECTIONS]; /**< First frame.                  */
	uint8_t flip  [XEEN_SPRITE_DIRECTIONS]; /**< Whether to flip horizontally. */
	uint8_t last  [XEEN_SPRITE_DIRECTIONS]; /**< Last frame.                   */
} XeenSpriteFrameInfo;

/** Read sprite information form a DAT file.
 *
 *  @param fp    File pointer.
 *  @param o     Offset to the sprite info data.
 *  @param i     Index of the sprite.
 *  @param info  Pointer to sprite info structure.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments
 *             - 2: File reading error.
 *
 *  @pre  File- and info pointer must be valid.
 *
 *  @post  The info pointer will contain the result.
 */
int xeen_read_sprite_info(FILE *fp, long o, int i, XeenSpriteFrameInfo *info);

#endif /* XEEN_DAT_TOOL_H */

