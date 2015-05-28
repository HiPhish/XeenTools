#ifndef XEEN_CHR_TOOL_H
#define XEEN_CHR_TOOL_H

/** @file chr_tool.h
 *
 *  Interface for the MAZE.CHR file.
 *
 *  This file stores information about the characters that can be in the party.
 *  Every entry is a player character (and hireling?) on its own. It does not
 *  store any information about the party though.
 *
 *  @TODO: We have no idea about the structure of items.
 *  @TODO: We have no idea about the bitfields for awards and spells.
 */

#include <stdint.h>
#include <stdio.h>

/** Sexes in a CHR file represented as bytes. */
enum xeen_chr_sex {
	XEEN_CHR_MALE   , /**< Male            */
	XEEN_CHR_FEMALE , /**< Female          */
	XEEN_CHR_SEXES  , /**< Number of sexes */
};

/** Races in a CHR file represented as bytes. */
enum xeen_chr_race {
	XEEN_CHR_HUMAN , /**< Human           */
	XEEN_CHR_ELF   , /**< Elf             */
	XEEN_CHR_DWARF , /**< Dwarf           */
	XEEN_CHR_GNOME , /**< Gnome           */
	XEEN_CHR_HORC  , /**< Half-orc        */
	XEEN_CHR_RACES , /**< Number of races */
};

/** Alignments in a CHR file represented as bytes. */
enum xeen_chr_alignment {
	XEEN_CHR_GOOD       , /**< Good                 */
	XEEN_CHR_NEUTRAL    , /**< Neutral              */
	XEEN_CHR_EVIL       , /**< Evil                 */
	XEEN_CHR_ALIGNMENTS , /**< Number of alignments */
};

/** Classes in a CHR file represented as bytes. */
enum xeen_chr_class {
	XEEN_CHR_KNIGHT    , /**< Knight.            */
	XEEN_CHR_PALADIN   , /**< Paladin.           */
	XEEN_CHR_ARCHER    , /**< Archer.            */
	XEEN_CHR_CLERIC    , /**< Cleric.            */
	XEEN_CHR_SORCERER  , /**< Sorcerer.          */
	XEEN_CHR_ROBBER    , /**< Robber.            */
	XEEN_CHR_NINJA     , /**< Ninja.             */
	XEEN_CHR_BARBARIAN , /**< Barbarian.         */
	XEEN_CHR_DRUID     , /**< Druid.             */
	XEEN_CHR_RANGER    , /**< Ranger.            */
	XEEN_CHR_CLASSES   , /**< Number of classes. */
};

/** Skills in a CHR file represented as bytes. */
enum xeen_chr_skill {
	XEEN_CHR_THIEVERY         , /**< Thievery         */
	XEEN_CHR_ARMSMASTER       , /**< Arms Master      */
	XEEN_CHR_ASTROLOGER       , /**< Astrologer       */
	XEEN_CHR_BODYBUILDER      , /**< Bodybuilder      */
	XEEN_CHR_CARTOGRAPHER     , /**< Cartography      */
	XEEN_CHR_CRUSADER         , /**< Crusader         */
	XEEN_CHR_DIRECTION        , /**< Direction Sense  */
	XEEN_CHR_LINGUIST         , /**< Linguist         */
	XEEN_CHR_MERCHANT         , /**< Merchant         */
	XEEN_CHR_MOUNTAINEER      , /**< Mountaineer      */
	XEEN_CHR_NAVIGATOR        , /**< Navigator        */
	XEEN_CHR_PATHFINDER       , /**< Pathfinder       */
	XEEN_CHR_PRAYERMASTER     , /**< Prayer Master    */
	XEEN_CHR_PRESTIDIGITATION , /**< Prestidigitation */
	XEEN_CHR_SWIMMING         , /**< Swimming         */
	XEEN_CHR_TRACKING         , /**< Tracking         */
	XEEN_CHR_SPOT             , /**< Spot secret door */
	XEEN_CHR_DANGER           , /**< Danger sense     */
	XEEN_CHR_SKILLS           , /**< Number of skills */
};

/** Conditions in a CHR file represented as bytes. */
enum xeen_chr_condition {
	XEEN_CHR_CURSED     , /**<Cursed       */
	XEEN_CHR_HEART      , /**<Heart Broken */
	XEEN_CHR_WEAK       , /**<Weak         */
	XEEN_CHR_POISONED   , /**<Poisoned     */
	XEEN_CHR_DISEASED   , /**<Diseased     */
	XEEN_CHR_INSANE     , /**<Insane       */
	XEEN_CHR_LOVE       , /**<In Love      */
	XEEN_CHR_DRUNK      , /**<Drunk        */
	XEEN_CHR_SLEEP      , /**<Sleep        */
	XEEN_CHR_DEPRESSED  , /**<Depressed    */
	XEEN_CHR_CONFUSED   , /**<Confused     */
	XEEN_CHR_PARALYZED  , /**<Paralyzed    */
	XEEN_CHR_CONDITIONS , /**<Paralyzed    */
};

/** Attributes in a CHR file represented as bytes. */
enum xeen_chr_attrib {
	XEEN_CHR_ATRRIB_MIGHT       , /**< Might       */
	XEEN_CHR_ATRRIB_INTELLECT   , /**< Intellect   */
	XEEN_CHR_ATRRIB_PERSONALITY , /**< Personality */
	XEEN_CHR_ATRRIB_ENDURANCE   , /**< Endurance   */
	XEEN_CHR_ATRRIB_SPEED       , /**< Speed       */
	XEEN_CHR_ATRRIB_ACCURACY    , /**< Accuracy    */
	XEEN_CHR_ATRRIB_LUCK        , /**< Luck        */
	XEEN_CHR_ATTRIBS,
};

/** Whether a statistic is permanent or temporary. */
enum xeen_chr_modifier {
	XEEN_CHR_PERM      , /**< Permanent            */
	XEEN_CHR_TEMP      , /**< Temporary            */
	XEEN_CHR_MODIFIERS , /**< Number of modifiers. */
};

/** Elements of damage. */
enum xeen_chr_element {
	XEEN_CHR_FIRE        , /**< Fire               */
	XEEN_CHR_COLD        , /**< Cold               */
	XEEN_CHR_ELECTRICITY , /**< Electricity        */
	XEEN_CHR_POISON      , /**< Poison             */
	XEEN_CHR_ENERGY      , /**< Energy             */
	XEEN_CHR_MAGIC       , /**< Magic              */
	XEEN_CHR_ELEMENTS    , /**< Number of elements */
};

/** Size of a CHR entry in bytes. */
#define XEEN_CHR_ENTRY_SIZE  354

/** Structure representing a CHR entry. */
typedef struct xeen_chr_entry {
	char     name[16];
	uint8_t  sex;
	uint8_t  race;
	uint8_t  side;
	uint8_t  class;
	uint8_t  attrib[XEEN_CHR_ATTRIBS][XEEN_CHR_MODIFIERS];
	uint8_t  ac_temp;
	uint8_t  level[XEEN_CHR_MODIFIERS];
	uint8_t  db_day;
	uint8_t  temp_age;
	uint8_t  skill[XEEN_CHR_SKILLS];
	uint8_t  award[64];
	uint8_t  spell[39];
	struct {
		uint8_t map;
		uint8_t side;
		uint8_t coordinate[2];
	} lloyd;
	uint8_t  has_spell;
	uint8_t  cur_spell;
	uint8_t  quick;
	uint8_t  weapon[36][4];
	uint8_t  armor[36][4];
	uint8_t  accessory[36][4];
	uint8_t  misc_item[36][4];
	uint8_t  resistance[XEEN_CHR_ELEMENTS][XEEN_CHR_MODIFIERS];
	uint8_t  condition[XEEN_CHR_CONDITIONS];
	uint8_t  unknown_1[2];
	uint8_t  unknown_2;
	uint16_t current_hp;
	uint16_t current_sp;
	uint16_t yb_day;
	uint32_t experience;
	uint8_t  spell_adv;
	uint8_t  spell_cmb;
} XeenChrEntry;

int xeen_chr_read_entry(FILE *fp, long o, int i, XeenChrEntry *entry);

#endif /* XEEN_CHR_TOOL_H */

