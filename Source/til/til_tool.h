#ifndef XEEN_TIL_TOOL_H
#define XEEN_TIL_TOOL_H

/** @file til_tool.h
 *
 *  Interface to TIL minimap sprites.
 *
 *  A TIL file is a sprite file that contains 52 tile frames and one large
 *  frame for the minimap canvas. The canvas is the last frame in the sprite.
 *
 *  All frames are static, except for the torch wall, which has five frames of
 *  animation.
 */

#include "../xeen/xeen.h"

/** List of tiles. */
enum xeen_til_tile {
	XEEN_TIL_FLOOR ,
	XEEN_TIL_FOG   ,
	XEEN_TIL_WALL_h,
	XEEN_TIL_WALL_v,
	XEEN_TIL_WALL_H_T_1,
	XEEN_TIL_WALL_V_T_1,
	XEEN_TIL_WALL_H_T_2,
	XEEN_TIL_WALL_V_T_2,
	XEEN_TIL_WALL_H_T_3,
	XEEN_TIL_WALL_V_T_3,
	XEEN_TIL_WALL_H_T_4,
	XEEN_TIL_WALL_V_T_4,
	XEEN_TIL_WALL_H_T_5,
	XEEN_TIL_WALL_H_V_5,
	XEEN_TIL_WINDOW_H,
	XEEN_TIL_WINDOW_V,
	XEEN_TIL_DOOR_H,
	XEEN_TIL_DOOR_V,
	XEEN_TIL_DOORWAY_H,
	XEEN_TIL_DOORWAY_V,
	XEEN_TIL_PORT_H_C,
	XEEN_TIL_PORT_V_C,
	XEEN_TIL_BASH_H,
	XEEN_TIL_BASH_V,
	XEEN_TIL_24,
	XEEN_TIL_25,
	XEEN_TIL_26,
	XEEN_TIL_27,
	XEEN_TIL_BANNER_H,
	XEEN_TIL_BANNER_V,
	XEEN_TIL_PORT_H_O,
	XEEN_TIL_PORT_V_O,
	XEEN_TIL_32,
	XEEN_TIL_33,
	XEEN_TIL_PILLAR_H,
	XEEN_TIL_PILLER_V,
	XEEN_TIL_WATER,
	XEEN_TIL_DIRT,
	XEEN_TIL_GRASS,
	XEEN_TIL_39,
	XEEN_TIL_SWAMP,
	XEEN_TIL_LAVA,
	XEEN_TIL_42,
	XEEN_TIL_43,
	XEEN_TIL_CARPET,
	XEEN_TIL_45,
	XEEN_TIL_46,
	XEEN_TIL_47,
	XEEN_TIL_48,
	XEEN_TIL_49,
	XEEN_TIL_50,
	XEEN_TIL_51,
	XEEN_TIL_TILES,
};

enum xeen_til_area {
	xeen_til_area_0,
	xeen_til_area_1,
	xeen_til_area_2,
	xeen_til_area_3,
	xeen_til_area_4,
	xeen_til_area_5,
	xeen_til_area_6,
	xeen_til_area_7,
	xeen_til_area_8,
	xeen_til_area_9,
	xeen_til_area_10,
	xeen_til_area_11,
	xeen_til_area_12,
	xeen_til_area_13,
	xeen_til_area_14,
	xeen_til_area_15,
	xeen_til_area_16,
	xeen_til_area_17,
	xeen_til_area_18,
	xeen_til_area_19,
	xeen_til_area_20,
	xeen_til_area_21,
	xeen_til_area_22,
	xeen_til_area_23,
	xeen_til_area_24,
	xeen_til_area_25,
	xeen_til_area_26,
	xeen_til_area_27,
	xeen_til_area_28,
	xeen_til_area_29,
	xeen_til_area_30,
	xeen_til_area_31,
	xeen_til_area_32,
	xeen_til_area_33,
	xeen_til_area_34,
	xeen_til_area_35,
	xeen_til_area_36,
	xeen_til_area_37,
	xeen_til_area_38,
	xeen_til_area_39,
	xeen_til_area_40,
	xeen_til_area_41,
	xeen_til_area_42,
	xeen_til_area_43,
	xeen_til_area_44,
	xeen_til_area_45,
	xeen_til_area_46,
	xeen_til_area_47,
	xeen_til_areas,
};

/** Size of a minimap tile. */
extern int xeen_til_size[XEEN_COORDS];

#endif /* XEEN_TIL_TOOL_H */

