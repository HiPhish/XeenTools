#include "fwl_tool.h"

char xeen_fwl_file_to_char[XEEN_FWL_FILES][1] = {
	[XEEN_FWL_1] = {[0] = '1'},
	[XEEN_FWL_2] = {[0] = '2'},
	[XEEN_FWL_3] = {[0] = '3'},
	[XEEN_FWL_4] = {[0] = '4'},
};

XeenFwlInfo xeen_fwl_table[XEEN_FWL_TYPES][XEEN_FWL_DISTANCES] = {
	[XEEN_FWL_STANDARD] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_1, .frame =  0, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame =  0, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 17, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame =  0, },
	},

	[XEEN_FWL_TORCH] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_1, .frame =  1, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame =  1, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 18, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame =  1, },
	},

	[XEEN_FWL_NICHE] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_1, .frame =  6, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame =  6, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 23, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame =  6, },
	},

	[XEEN_FWL_UNKNOWN] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_1, .frame =  7, },
		[XEEN_FWL_CLOSE] = { .file =          0, .frame =  0, },
		[XEEN_FWL_NEAR]  = { .file =          0, .frame =  0, },
		[XEEN_FWL_FAR]   = { .file =          0, .frame =  0, },
	},

	[XEEN_FWL_DOOR_C] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_2, .frame =  0, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame =  7, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 24, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame =  7, },
	},

	[XEEN_FWL_DOOR_O] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_2, .frame =  1, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame =  8, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 25, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame =  8, },
	},

	[XEEN_FWL_GRATE_C] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_2, .frame =  2, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame =  9, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 26, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame =  9, },
	},

	[XEEN_FWL_BASHED] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_2, .frame =  3, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame = 10, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 27, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame = 10, },
	},

	[XEEN_FWL_LADDER_U] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_2, .frame =  4, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame = 11, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 28, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame = 11, },
	},

	[XEEN_FWL_LADDER_D] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_2, .frame =  5, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame = 12, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 29, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame = 12, },
	},

	[XEEN_FWL_SAVE_C] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_2, .frame =  6, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame = 13, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 30, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame = 13, },
	},

	[XEEN_FWL_GRATE_O] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_2, .frame =  7, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame = 14, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 31, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame = 14, },
	},

	[XEEN_FWL_SAVE_O] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_2, .frame =  8, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame = 15, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 32, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame = 15, },
	},

	[XEEN_FWL_POSTS] = {
		[XEEN_FWL_NEXT]  = { .file = XEEN_FWL_2, .frame =  9, },
		[XEEN_FWL_CLOSE] = { .file = XEEN_FWL_3, .frame = 16, },
		[XEEN_FWL_NEAR]  = { .file = XEEN_FWL_3, .frame = 33, },
		[XEEN_FWL_FAR]   = { .file = XEEN_FWL_4, .frame = 16, },
	},
};
