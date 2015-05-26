#include "cfg_tool.h"

/** Convert two bytes to an unsigned 16-bit integer. 
 *
 *  @param le  Little end.
 *  @param be  Big end.
 *
 *  @return  The unsigned 16-bit integer.
 *
 *  This function converts regardless of the target machine's endianess. 
 */
uint16_t bytes_to_uint16(uint8_t le, uint8_t be);

int xeen_read_cfg(FILE *fp, XeenCfg *cfg) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		FREAD_FAIL,
	} error = SUCCESS;
	uint8_t bytes[28];

	/* Pre-conditions */
	if (!fp || !cfg) {
		error = INVALID_ARGS;
		goto end;
	}

	if (fread(bytes, sizeof(uint8_t), 28, fp) != 28 * sizeof(uint8_t)) {
		error = FREAD_FAIL;
		goto end;
	}

	*cfg = (XeenCfg) {
		.sound_card    = bytes_to_uint16(bytes[0x00], bytes[0x01]),
		.sound_address = bytes_to_uint16(bytes[0x02], bytes[0x03]),

		.music_card    = bytes_to_uint16(bytes[0x04], bytes[0x05]),
		.music_address = bytes_to_uint16(bytes[0x06], bytes[0x07]),

		.irq           = bytes_to_uint16(bytes[0x08], bytes[0x09]),

		.ereiamjh = {
			bytes[0x0A + 0x00],
			bytes[0x0A + 0x01],
			bytes[0x0A + 0x02],
			bytes[0x0A + 0x03],
			bytes[0x0A + 0x04],
			bytes[0x0A + 0x05],
			bytes[0x0A + 0x06],
			bytes[0x0A + 0x07],
		},

		.has_386        = bytes_to_uint16(bytes[0x12], bytes[0x13]),

		.volume_set     = bytes_to_uint16(bytes[0x14], bytes[0x15]),

		.won_darkside   = bytes[0x16],
		.won_third      = bytes[0x17],

		.sound_dma      = bytes_to_uint16(bytes[0x18], bytes[0x19]),

		.saw_dark_intro = bytes_to_uint16(bytes[0x1a], bytes[0x1b]),
	};

end:
	return error;
}

uint16_t bytes_to_uint16(uint8_t le, uint8_t be) {
	return ((uint16_t)be << 8) + (uint16_t)le;
}
