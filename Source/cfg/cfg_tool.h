#ifndef XEEN_CFG_TOOL_H
#define XEEN_CFG_TOOL_H

/** @file cfg_tool.h
 *
 *  Interface for CFG configuration files.
 *
 *  This interface provides a structure to encapsulate the *Wold of Xeen*
 *  configuration files. It reads the entire file in one go and wraps all the
 *  information into the structure, even the information that appears useless
 *  or irrelevant on modern systems.
 *
 *  Since the original game will refuse to start if there is no configuration
 *  file this feature could be still useful when bridging back to the original.
 *
 *  All structure members have their original data size, so if a particular
 *  member is stored as an unsigned 16-bit integer it means it was stored as
 *  tow bytes originally. All multi-byte integers were stored as little-endian
 *  numbers.
 */

#include <stdint.h>
#include <stdio.h>

/** Structure of a XEEN configuration file. */
typedef struct xeen_cfg {
	uint16_t sound_card;
	uint16_t sound_address;

	uint16_t music_card;
	uint16_t music_address;

	uint16_t irq;

	uint8_t ereiamjh[8];

	uint16_t has_386;

	uint16_t volume_set;

	uint8_t won_darkside;
	uint8_t won_third;

	uint16_t sound_dma;

	uint16_t saw_dark_intro;
} XeenCfg;

/** Read configuration information form a CFG file.
 *
 *  @param fp    File pointer.
 *  @param info  Pointer to CFG structure.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments
 *             - 2: File reading error.
 *
 *  @pre  File- and CFG pointer must be valid.
 *
 *  @post  The CFG pointer will contain the result.
 */
int xeen_read_cfg(FILE *fp, XeenCfg *cfg);

#endif /* XEEN_CFG_TOOL_H */

