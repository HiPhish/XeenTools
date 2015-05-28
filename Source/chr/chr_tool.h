#ifndef XEEN_CHR_TOOL_H
#define XEEN_CHR_TOOL_H

enum xeen_chr_sex {
	XEEN_CHR_MALE   , /**< Male.   */
	XEEN_CHR_FEMALE , /**< Female. */
	XEEN_CHR_SEXES  , /**< Male.   */
};

enum xeen_chr_race {
	XEEN_CHR_HUMAN , /**< Human           */
	XEEN_CHR_ELF   , /**< Elf             */
	XEEN_CHR_DWARF , /**< Dwarf           */
	XEEN_CHR_GNOME , /**< Gnome           */
	XEEN_CHR_HORC  , /**< Half-orc        */
	XEEN_CHR_RACES , /**< Number of races */
};

enum xeen_chr_alignment {
	XEEN_CHR_GOOD       , /**< Good                 */
	XEEN_CHR_NEUTRAL    , /**< Neutral              */
	XEEN_CHR_EVIL       , /**< Evil                 */
	XEEN_CHR_ALIGNMENTS , /**< Number of alignments */
};

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

enum xeen_chr_skill {
	XEEN_CHR_THIEVERY       , /**< Thievery         */
	XEEN_CHR_ARMSMASTER     , /**< Arms Master      */
	XEEN_CHR_ASTROLOGER     , /**< Astrologer       */
	XEEN_CHR_BODYBUILDER    , /**< Bodybuilder      */
	XEEN_CHR_CARTOGRAPHER   , /**< Cartography      */
	XEEN_CHR_CRUSADER       , /**< Crusader         */
	XEEN_CHR_DIRECTION      , /**< Direction Sense  */
	XEEN_CHR_LINGUIST       , /**< Linguist         */
	XEEN_CHR_MERCHANT       , /**< Merchant         */
	XEEN_CHR_MOUNTAINEER    , /**< Mountaineer      */
	XEEN_CHR_NAVIGATOR      , /**< Navigator        */
	XEEN_CHR_PATHFINDER     , /**< Pathfinder       */
	XEEN_CHR_PRAYER         , /**< Prayer Master    */
	XEEN_CHR_PRESTIDIGATION , /**< Prestidigation   */
	XEEN_CHR_SWIMMING       , /**< Swimming         */
	XEEN_CHR_TRACKING       , /**< Tracking         */
	XEEN_CHR_SPOT           , /**< Spot secret door */
	XEEN_CHR_DANGER         , /**< Danger sense     */
	XEEN_CHR_SKILLS         , /**< Number of skills */
};

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
	XEEN_CHR_conditions , /**<Paralyzed    */
};

#endif /* XEEN_CHR_TOOL_H */

