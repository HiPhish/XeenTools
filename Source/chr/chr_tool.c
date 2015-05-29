#include "chr_tool.h"

int xeen_chr_read_entry(FILE *fp, long o, int i, XeenChrEntry *entry) {
	enum {
		SUCCESS,
		INVALID_ARGS,
		FREAD_FAIL,
	} error = SUCCESS;

	if (!fp || !entry) {
		error = INVALID_ARGS;
		goto end;
	}

	uint8_t bytes[XEEN_CHR_ENTRY_SIZE];
	if (fread(bytes, sizeof(uint8_t), XEEN_CHR_ENTRY_SIZE, fp) != XEEN_CHR_ENTRY_SIZE * sizeof(uint8_t)) {
		error = FREAD_FAIL;
		goto end;
	}

	*entry = (XeenChrEntry) {
		.name = {
			[0x0] = bytes[0x000], [0x1] = bytes[0x001], [0x2] = bytes[0x002], [0x3] = bytes[0x003],
			[0x4] = bytes[0x004], [0x5] = bytes[0x005], [0x6] = bytes[0x006], [0x7] = bytes[0x007],
			[0x8] = bytes[0x008], [0x9] = bytes[0x009], [0xA] = bytes[0x00A], [0xB] = bytes[0x00B],
			[0xC] = bytes[0x00C], [0xD] = bytes[0x00D], [0xE] = bytes[0x00E], [0xF] = bytes[0x00F],
		},
		.sex   = bytes[0x010],
		.race  = bytes[0x011],
		.side  = bytes[0x012],
		.class = bytes[0x013],

		#define ATTRIB_FIELD(attrib)\
			[attrib] = {\
				[XEEN_CHR_PERM] = bytes[0x014+attrib*XEEN_CHR_MODIFIERS+XEEN_CHR_PERM],\
				[XEEN_CHR_TEMP] = bytes[0x014+attrib*XEEN_CHR_MODIFIERS+XEEN_CHR_TEMP],\
			},
			
		.attrib = {
			ATTRIB_FIELD( XEEN_CHR_ATRRIB_MIGHT       )
			ATTRIB_FIELD( XEEN_CHR_ATRRIB_INTELLECT   )
			ATTRIB_FIELD( XEEN_CHR_ATRRIB_PERSONALITY )
			ATTRIB_FIELD( XEEN_CHR_ATRRIB_ENDURANCE   )
			ATTRIB_FIELD( XEEN_CHR_ATRRIB_SPEED       )
			ATTRIB_FIELD( XEEN_CHR_ATRRIB_ACCURACY    )
			ATTRIB_FIELD( XEEN_CHR_ATRRIB_LUCK        )
		},
		#undef ATTRIB_FIELD

		.ac_temp = bytes[0x022],
		.level   = {
			[XEEN_CHR_PERM] = bytes[0x023 + XEEN_CHR_PERM],
			[XEEN_CHR_TEMP] = bytes[0x023 + XEEN_CHR_TEMP],
		},
		.db_day   = bytes[0x025],
		.temp_age = bytes[0x026],
		.skill = {
			[XEEN_CHR_THIEVERY         ] = bytes[0x027 + XEEN_CHR_THIEVERY         ],
			[XEEN_CHR_ARMSMASTER       ] = bytes[0x027 + XEEN_CHR_ARMSMASTER       ],
			[XEEN_CHR_ASTROLOGER       ] = bytes[0x027 + XEEN_CHR_ASTROLOGER       ],
			[XEEN_CHR_BODYBUILDER      ] = bytes[0x027 + XEEN_CHR_BODYBUILDER      ],
			[XEEN_CHR_CARTOGRAPHER     ] = bytes[0x027 + XEEN_CHR_CARTOGRAPHER     ],
			[XEEN_CHR_CRUSADER         ] = bytes[0x027 + XEEN_CHR_CRUSADER         ],
			[XEEN_CHR_DIRECTION        ] = bytes[0x027 + XEEN_CHR_DIRECTION        ],
			[XEEN_CHR_LINGUIST         ] = bytes[0x027 + XEEN_CHR_LINGUIST         ],
			[XEEN_CHR_MERCHANT         ] = bytes[0x027 + XEEN_CHR_MERCHANT         ],
			[XEEN_CHR_MOUNTAINEER      ] = bytes[0x027 + XEEN_CHR_MOUNTAINEER      ],
			[XEEN_CHR_NAVIGATOR        ] = bytes[0x027 + XEEN_CHR_NAVIGATOR        ],
			[XEEN_CHR_PATHFINDER       ] = bytes[0x027 + XEEN_CHR_PATHFINDER       ],
			[XEEN_CHR_PRAYERMASTER     ] = bytes[0x027 + XEEN_CHR_PRAYERMASTER     ],
			[XEEN_CHR_PRESTIDIGITATION ] = bytes[0x027 + XEEN_CHR_PRESTIDIGITATION ],
			[XEEN_CHR_SWIMMING         ] = bytes[0x027 + XEEN_CHR_SWIMMING         ],
			[XEEN_CHR_TRACKING         ] = bytes[0x027 + XEEN_CHR_TRACKING         ],
			[XEEN_CHR_SPOT             ] = bytes[0x027 + XEEN_CHR_SPOT             ],
			[XEEN_CHR_DANGER           ] = bytes[0x027 + XEEN_CHR_DANGER           ],
		},
		.award = {
			/* This is just the bytes dumped as they were read */
			#define OFS  0x039
			#define b    bytes
			[ 0] = b[OFS+ 0], [ 1] = b[OFS+ 1], [ 2] = b[OFS+ 2], [ 3] = b[OFS+ 3],
			[ 4] = b[OFS+ 4], [ 5] = b[OFS+ 5], [ 6] = b[OFS+ 6], [ 7] = b[OFS+ 7],
			[ 8] = b[OFS+ 8], [ 9] = b[OFS+ 9], [10] = b[OFS+10], [11] = b[OFS+11],
			[12] = b[OFS+12], [13] = b[OFS+13], [14] = b[OFS+14], [15] = b[OFS+15],
			[16] = b[OFS+16], [17] = b[OFS+17], [18] = b[OFS+18], [19] = b[OFS+19],
			[20] = b[OFS+20], [21] = b[OFS+21], [22] = b[OFS+22], [23] = b[OFS+23],
			[24] = b[OFS+24], [25] = b[OFS+25], [26] = b[OFS+26], [27] = b[OFS+27],
			[28] = b[OFS+28], [29] = b[OFS+29], [30] = b[OFS+30], [31] = b[OFS+31],
			[32] = b[OFS+32], [33] = b[OFS+33], [34] = b[OFS+34], [35] = b[OFS+35],
			[36] = b[OFS+36], [37] = b[OFS+37], [38] = b[OFS+38], [39] = b[OFS+39],
			[40] = b[OFS+40], [41] = b[OFS+41], [42] = b[OFS+42], [43] = b[OFS+43],
			[44] = b[OFS+44], [45] = b[OFS+45], [46] = b[OFS+46], [47] = b[OFS+47],
			[48] = b[OFS+48], [49] = b[OFS+49], [50] = b[OFS+50], [51] = b[OFS+51],
			[52] = b[OFS+52], [53] = b[OFS+53], [54] = b[OFS+54], [55] = b[OFS+55],
			[56] = b[OFS+56], [57] = b[OFS+57], [58] = b[OFS+58], [59] = b[OFS+59],
			[60] = b[OFS+60], [61] = b[OFS+61], [62] = b[OFS+62], [63] = b[OFS+63],
			#undef OFS
			#undef b
		},
		.spell = {
			#define OFS  0x079
			#define b    bytes
			[ 0] = b[OFS+ 0], [ 1] = b[OFS+ 1], [ 2] = b[OFS+ 2], [ 3] = b[OFS+ 3],
			[ 4] = b[OFS+ 4], [ 5] = b[OFS+ 5], [ 6] = b[OFS+ 6], [ 7] = b[OFS+ 7],
			[ 8] = b[OFS+ 8], [ 9] = b[OFS+ 9], [10] = b[OFS+10], [11] = b[OFS+11],
			[12] = b[OFS+12], [13] = b[OFS+13], [14] = b[OFS+14], [15] = b[OFS+15],
			[16] = b[OFS+16], [17] = b[OFS+17], [18] = b[OFS+18], [19] = b[OFS+19],
			[20] = b[OFS+20], [21] = b[OFS+21], [22] = b[OFS+22], [23] = b[OFS+23],
			[24] = b[OFS+24], [25] = b[OFS+25], [26] = b[OFS+26], [27] = b[OFS+27],
			[28] = b[OFS+28], [29] = b[OFS+29], [30] = b[OFS+30], [31] = b[OFS+31],
			[32] = b[OFS+32], [33] = b[OFS+33], [34] = b[OFS+34], [35] = b[OFS+35],
			[36] = b[OFS+36], [37] = b[OFS+37], [38] = b[OFS+38],
			#undef OFS
			#undef b
		},
		.lloyd = {
			.map  = bytes[0x0A0],
			.side = bytes[0x136], /* <- That's not a typo */
			.coordinate = { [0] = bytes[0x0A1 + 0], [1] = bytes[0x0A1 + 1], },
		},
		.has_spell = bytes[0x0A3],
		.cur_spell = bytes[0x0A4],
		.quick     = bytes[0x0A5],

		#define ITEM(i) \
			[i] = { \
				.id        = bytes[OFS + i*4 + 0],                         \
				.element   = bytes[OFS + i*4 + 1] - 0,                     \
				.material  = bytes[OFS + i*4 + 1] - XEEN_ITEM_E_ELEMENTS,  \
				.attribute = bytes[OFS + i*4 + 1] - XEEN_ITEM_M_MATERIALS, \
				.suffix    = bytes[OFS + i*4 + 2],                         \
				.condition = bytes[OFS + i*4 + 3],                         \
			}
		.weapon = {
			#define OFS  0x0A6
			ITEM(0), ITEM(1), ITEM(2),
			ITEM(3), ITEM(4), ITEM(5),
			ITEM(6), ITEM(7), ITEM(8),
			#undef OFS
		},
		.armor = {
			#define OFS  0x0CA
			ITEM(0), ITEM(1), ITEM(2),
			ITEM(3), ITEM(4), ITEM(5),
			ITEM(6), ITEM(7), ITEM(8),
			#undef OFS
		},
		.accessory = {
			#define OFS  0x0EE
			ITEM(0), ITEM(1), ITEM(2),
			ITEM(3), ITEM(4), ITEM(5),
			ITEM(6), ITEM(7), ITEM(8),
			#undef OFS
		},
		.misc_item = {
			#define OFS  0x112
			ITEM(0), ITEM(1), ITEM(2),
			ITEM(3), ITEM(4), ITEM(5),
			ITEM(6), ITEM(7), ITEM(8),
			#undef OFS
		},
		#undef ITEM

		.resistance = {
			#define OFS  0x137
			#define RESISTANCE(e)\
				[e] = {\
					[XEEN_CHR_TEMP] = bytes[OFS + e*XEEN_CHR_MODIFIERS + XEEN_CHR_TEMP],\
					[XEEN_CHR_PERM] = bytes[OFS + e*XEEN_CHR_MODIFIERS + XEEN_CHR_PERM],\
				}

			RESISTANCE( XEEN_CHR_FIRE        ), RESISTANCE( XEEN_CHR_COLD   ), 
			RESISTANCE( XEEN_CHR_ELECTRICITY ), RESISTANCE( XEEN_CHR_POISON ), 
			RESISTANCE( XEEN_CHR_ENERGY      ), RESISTANCE( XEEN_CHR_MAGIC  ), 
			#undef RESISTANCE
			#undef OFS
		},

		.condition = {
			[XEEN_CHR_CURSED   ] = bytes[0x143 + XEEN_CHR_CURSED    ],
			[XEEN_CHR_HEART    ] = bytes[0x143 + XEEN_CHR_HEART     ],
			[XEEN_CHR_WEAK     ] = bytes[0x143 + XEEN_CHR_WEAK      ],
			[XEEN_CHR_POISONED ] = bytes[0x143 + XEEN_CHR_POISONED  ],
			[XEEN_CHR_DISEASED ] = bytes[0x143 + XEEN_CHR_DISEASED  ],
			[XEEN_CHR_INSANE   ] = bytes[0x143 + XEEN_CHR_INSANE    ],
			[XEEN_CHR_LOVE     ] = bytes[0x143 + XEEN_CHR_LOVE      ],
			[XEEN_CHR_DRUNK    ] = bytes[0x143 + XEEN_CHR_DRUNK     ],
			[XEEN_CHR_SLEEP    ] = bytes[0x143 + XEEN_CHR_SLEEP     ],
			[XEEN_CHR_DEPRESSED] = bytes[0x143 + XEEN_CHR_DEPRESSED ],
			[XEEN_CHR_CONFUSED ] = bytes[0x143 + XEEN_CHR_CONFUSED  ],
			[XEEN_CHR_PARALYZED] = bytes[0x143 + XEEN_CHR_PARALYZED ],
		},

		.unknown_1 = {bytes[0x153], bytes[0x154]},
		.unknown_2 = bytes[0x155],

		.current_hp = ((uint16_t)bytes[0x157] <<  8) + ((uint16_t)bytes[0x156] <<  0),
		.current_sp = ((uint16_t)bytes[0x159] <<  8) + ((uint16_t)bytes[0x158] <<  0),
		.yb_day     = ((uint16_t)bytes[0x15B] <<  8) + ((uint16_t)bytes[0x15A] <<  0),
		.experience = ((uint16_t)bytes[0x15F] << 24) + ((uint16_t)bytes[0x15E] << 16)
		            + ((uint16_t)bytes[0x15D] <<  8) + ((uint16_t)bytes[0x15C] <<  0),

		.spell_adv = bytes[0x160],
		.spell_cmb = bytes[0x161],
	};

end:
	return error;
}

