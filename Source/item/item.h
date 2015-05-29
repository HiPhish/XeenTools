#ifndef XEEN_ITEM_H
#define XEEN_ITEM_H

#include <stdint.h>

/** Elemental enchantments for items. */
enum xeen_item_element {
	XEEN_ITEM_E_BURNING      , /**< Burning     */
	XEEN_ITEM_E_FIERY        , /**< Fiery       */
	XEEN_ITEM_E_PYRIC        , /**< Pyric       */
	XEEN_ITEM_E_FUMING       , /**< Fuming      */
	XEEN_ITEM_E_FLAMING      , /**< Flaming     */
	XEEN_ITEM_E_SEETHING     , /**< Seething    */
	XEEN_ITEM_E_BLAZING      , /**< Blazing     */
	XEEN_ITEM_E_SCORCHING    , /**< Scorching   */
	XEEN_ITEM_E_FLICKERING   , /**< Flickering  */
	XEEN_ITEM_E_SPARKING     , /**< Sparking    */
	XEEN_ITEM_E_STATIC       , /**< Static      */
	XEEN_ITEM_E_FLASHING     , /**< Flashing    */
	XEEN_ITEM_E_SHOCKING     , /**< Shocking    */
	XEEN_ITEM_E_ELECTRIC     , /**< Electric    */
	XEEN_ITEM_E_DYNA         , /**< Dyna        */
	XEEN_ITEM_E_ICY          , /**< Icy         */
	XEEN_ITEM_E_FROST        , /**< Frost       */
	XEEN_ITEM_E_FREEZING     , /**< Freezing    */
	XEEN_ITEM_E_COLD         , /**< Cold        */
	XEEN_ITEM_E_CRYO         , /**< Cryo        */
	XEEN_ITEM_E_ACIDIC       , /**< Acidic      */
	XEEN_ITEM_E_VENEMOUS     , /**< Venemous    */
	XEEN_ITEM_E_POISONOUS    , /**< Poisonous   */
	XEEN_ITEM_E_TOXIC        , /**< Toxic       */
	XEEN_ITEM_E_NOXIOUS      , /**< Noxious     */
	XEEN_ITEM_E_GLOWING      , /**< Glowing     */
	XEEN_ITEM_E_INCANDESCENT , /**< Incandescent*/
	XEEN_ITEM_E_DENSE        , /**< Dense       */
	XEEN_ITEM_E_SONIC        , /**< Sonic       */
	XEEN_ITEM_E_POWER        , /**< Power       */
	XEEN_ITEM_E_THERMAL      , /**< Thermal     */
	XEEN_ITEM_E_RADIATING    , /**< Radiating   */
	XEEN_ITEM_E_KINETIC      , /**< Kinetic     */
	XEEN_ITEM_E_MYSTIC       , /**< Mystic      */
	XEEN_ITEM_E_MAGICAL      , /**< Magical     */
	XEEN_ITEM_E_ECTOPLASMIC  , /**< Ectoplasmic */
	XEEN_ITEM_E_ELEMENTS     ,
};

/** List of item materials. */
enum xeen_item_material {
	XEEN_ITEM_M_WOODEN    , /**< Wooden   */
	XEEN_ITEM_M_LEATHER   , /**< Leather  */
	XEEN_ITEM_M_BRASS     , /**< Brass    */
	XEEN_ITEM_M_BRONZE    , /**< Bronze   */
	XEEN_ITEM_M_GLASS     , /**< Glass    */
	XEEN_ITEM_M_CORAL     , /**< Coral    */
	XEEN_ITEM_M_CRYSTAL   , /**< Crystal  */
	XEEN_ITEM_M_IRON      , /**< Iron     */	
	XEEN_ITEM_M_LAPIS     , /**< Lapis    */
	XEEN_ITEM_M_PEARL     , /**< Pearl    */
	XEEN_ITEM_M_SILVER    , /**< Silver   */
	XEEN_ITEM_M_AMBER     , /**< Amber    */
	XEEN_ITEM_M_EBONY     , /**< Ebony    */
	XEEN_ITEM_M_STEEL     , /**< Steel    */
	XEEN_ITEM_M_QUARTZ    , /**< Quartz   */
	XEEN_ITEM_M_GOLD      , /**< Gold     */
	XEEN_ITEM_M_PLATINUM  , /**< Platinum */
	XEEN_ITEM_M_RUBY      , /**< Ruby     */
	XEEN_ITEM_M_EMERALD   , /**< Emerald  */
	XEEN_ITEM_M_SAPPHIRE  , /**< Sapphire */
	XEEN_ITEM_M_DIAMOND   , /**< Diamond  */
	XEEN_ITEM_M_OBSIDIAN  , /**< Obsidian */
	XEEN_ITEM_M_MATERIALS ,
};

enum xeen_item_attrib {
	XEEN_ITEM_A_MIGHT       , /**< Might       */
	XEEN_ITEM_A_STRENGTH    , /**< Strength    */
	XEEN_ITEM_A_WARRIOR     , /**< Warrior     */
	XEEN_ITEM_A_OGRE        , /**< Ogre        */
	XEEN_ITEM_A_GIANT       , /**< Giant       */
	XEEN_ITEM_A_THUNDER     , /**< Thunder     */
	XEEN_ITEM_A_FORCE       , /**< Force       */
	XEEN_ITEM_A_POWER       , /**< Power       */
	XEEN_ITEM_A_DRAGON      , /**< Dragon      */
	XEEN_ITEM_A_PHOTON      , /**< Photon      */
	XEEN_ITEM_A_CLEVER      , /**< Clever      */
	XEEN_ITEM_A_MIND        , /**< Mind        */
	XEEN_ITEM_A_SAGE        , /**< Sage        */
	XEEN_ITEM_A_THOUGHT     , /**< Thought     */
	XEEN_ITEM_A_KNOWLEDGE   , /**< Knowledge   */
	XEEN_ITEM_A_INTELLECT   , /**< Intellect   */
	XEEN_ITEM_A_WISDOM      , /**< Wisdom      */
	XEEN_ITEM_A_GENIUS      , /**< Genius      */
	XEEN_ITEM_A_BUDDY       , /**< Buddy       */
	XEEN_ITEM_A_FRIENDSHIP  , /**< Friendship  */
	XEEN_ITEM_A_CHARM       , /**< Charm       */
	XEEN_ITEM_A_PERSONALITY , /**< Personality */
	XEEN_ITEM_A_CHARISMA    , /**< Charisma    */
	XEEN_ITEM_A_LEADERSHIP  , /**< Leadership  */
	XEEN_ITEM_A_EGO         , /**< Ego         */
	XEEN_ITEM_A_HOLY        , /**< Holy        */
	XEEN_ITEM_A_QUICK       , /**< Quick       */
	XEEN_ITEM_A_SWIFT       , /**< Swift       */
	XEEN_ITEM_A_FAST        , /**< Fast        */
	XEEN_ITEM_A_RAPID       , /**< Rapid       */
	XEEN_ITEM_A_SPEED       , /**< Speed       */
	XEEN_ITEM_A_WIND        , /**< Wind        */
	XEEN_ITEM_A_ACCELERATOR , /**< Accelerator */
	XEEN_ITEM_A_VELOCITY    , /**< Velocity    */
	XEEN_ITEM_A_SHARP       , /**< Sharp       */
	XEEN_ITEM_A_ACCURATE    , /**< Accurate    */
	XEEN_ITEM_A_MARKSMAN    , /**< Marksman    */
	XEEN_ITEM_A_PRECISION   , /**< Precision   */
	XEEN_ITEM_A_TRUE        , /**< True        */
	XEEN_ITEM_A_EXACTO      , /**< Exacto      */
	XEEN_ITEM_A_CLOVER      , /**< Clover      */
	XEEN_ITEM_A_CHANCE      , /**< Chance      */
	XEEN_ITEM_A_WINNERS     , /**< Winners     */
	XEEN_ITEM_A_LUCKY       , /**< Lucky       */
	XEEN_ITEM_A_GAMBLERS    , /**< Gamblers    */
	XEEN_ITEM_A_LEPRECHAUNS , /**< Leprechauns */
	XEEN_ITEM_A_VIGOR       , /**< Vigor       */
	XEEN_ITEM_A_HEALTH      , /**< Health      */
	XEEN_ITEM_A_LIFE        , /**< Life        */
	XEEN_ITEM_A_TROLL       , /**< Troll       */
	XEEN_ITEM_A_VAMPIRIC    , /**< Vampiric    */
	XEEN_ITEM_A_SPELL       , /**< Spell       */
	XEEN_ITEM_A_CASTORS     , /**< Castors     */
	XEEN_ITEM_A_WITCH       , /**< Witch       */
	XEEN_ITEM_A_MAGE        , /**< Mage        */
	XEEN_ITEM_A_ARCHMAGE    , /**< Archmage    */
	XEEN_ITEM_A_ARCANE      , /**< Arcane      */
	XEEN_ITEM_A_PROTECTION  , /**< Protection  */
	XEEN_ITEM_A_ARMORED     , /**< Armored     */
	XEEN_ITEM_A_DEFENDER    , /**< Defender    */
	XEEN_ITEM_A_STEALTH     , /**< Stealth     */
	XEEN_ITEM_A_DIVINE      , /**< Divine      */
	XEEN_ITEM_A_MUGGER      , /**< Mugger      */
	XEEN_ITEM_A_BURGLER     , /**< Burgler     */
	XEEN_ITEM_A_LOOTER      , /**< Looter      */
	XEEN_ITEM_A_BRIGAND     , /**< Brigand     */
	XEEN_ITEM_A_FILCH       , /**< Filch       */
	XEEN_ITEM_A_THIEF       , /**< Thief       */
	XEEN_ITEM_A_ROGUE       , /**< Rogue       */
	XEEN_ITEM_A_PLUNDER     , /**< Plunder     */
	XEEN_ITEM_A_CRIMINAL    , /**< Criminal    */
	XEEN_ITEM_A_PIRATE      , /**< Pirate      */
	XEEN_ITEM_A_ATTRIBUTES  , /**< Attributes  */
};

enum xeen_item_suffix {
	XEEN_ITEM_DRAGON_SLAYER  , /**< Dragon_Slayer  */
	XEEN_ITEM_UNDEAD_EATER   , /**< Undead_Eater   */
	XEEN_ITEM_GOLEM_SMASHER  , /**< Golem_Smasher  */
	XEEN_ITEM_BUG_ZAPPER     , /**< Bug_Zapper     */
	XEEN_ITEM_MONSTER_MASHER , /**< Monster_Masher */
	XEEN_ITEM_BEAST_BOPPER   , /**< Beast_Bopper   */
	XEEN_ITEM_SUFFIX         , /**< Suffixes       */
};

/** Structure of an item. */
typedef struct xeen_item {
	uint8_t id        ; /**< Base item ID.               */
	uint8_t element   ; /**< Elemental enchantment.      */
	uint8_t material  ; /**< Material.                   */
	uint8_t attribute ; /**< Attribute bonus.            */
	uint8_t suffix    ; /**< Special suffix for weapons. */
	uint8_t condition ; /**< Condition (broken, etc.).   */
} XeenItem;

#endif /* XEEN_ITEM_H */

