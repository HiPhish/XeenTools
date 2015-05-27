#ifndef XEEN_ENV_TOOL_H
#define XEEN_ENV_TOOL_H

/** @file env_tool.h
 *
 *  Just constants and their strings, for environment sets.
 */

enum xeen_env_set {
	XEEN_CAVE,     /**< Cave.                       */
	XEEN_CSTL,     /**< Castle.                     */
	XEEN_DUNG,     /**< Dungeon.                    */
	XEEN_SCFI,     /**< Sci-Fi.                     */
	XEEN_TOWN,     /**< Town.                       */
	XEEN_TOWR,     /**< Tower.                      */
	XEEN_ENV_SETS, /**< Number of environment sets. */
};

enum xeen_env_type {
	SKY,            /**< Sky.                         */
	GND,            /**< Ground.                      */
	TIL,            /**< Tile-set.                    */
	FWL,            /**< Front-wall.                  */
	SWL,            /**< Side-wall.                   */
	XEEN_ENV_TYPES, /**< Number of environment types. */
};

/** Map environment sets to strings. */
char xeen_env_set_string[XEEN_ENV_SETS][4] = {
	[XEEN_CAVE] = "CAVE", /**< Cave.    */
	[XEEN_CSTL] = "CSTL", /**< Castle.  */
	[XEEN_DUNG] = "DUNG", /**< Dungeon. */
	[XEEN_SCFI] = "SCFI", /**< Sci-Fi.  */
	[XEEN_TOWN] = "TOWN", /**< Town.    */
	[XEEN_TOWR] = "TOWR", /**< Tower.   */
};

/** Map environment types to strings. */
char xeen_env_type_string[XEEN_ENV_TYPES][3] = {
	[SKY] = "SKY",
	[GND] = "GND",
	[TIL] = "TIL",
	[FWL] = "FWL",
	[SWL] = "SWL",
};

#endif /* XEEN_ENV_TOOL_H */

