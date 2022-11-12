//
//  enchantment.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef enchantment_type_h
#define enchantment_type_h

#include "enchantment_target.h"

struct EnchantmentType {
    const char identifier[16];
    const struct EnchantmentType *incompatible_with;
};

/// Increases underwater mining speed.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_AQUA_AFFINITY;
/// Increases damage to arthropod mobs.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_BANE_OF_ARTHROPODS;
/// Prevents the cursed item, usually a piece of armor, from being unequipped in Survival mode.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_BINDING_CURSE;
/// Reduces damage taken from explosions.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_BLAST_PROTECTION;
/// Strikes the hit mob with a lightning bolt, if the mob is in the rain.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_CHANNELING;
/// Increases underwater movement speed.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_DEPTH_STRIDER;
/// Increases mining speed.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_EFFICIENCY;
/// Reduces damage taken from falling and natural teleportation.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_FEATHER_FALLING;
/// Sets victim ablaze when attacked via melee.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_FIRE_ASPECT;
/// Significantly reduces damage taken from fire and lava.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_FIRE_PROTECTION;
/// Sets victim ablaze when attacked via projectile.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_FLAME;
/// Increases block drop chances and amount droppedt;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_FORTUNE;
/// Temporarily changes nearby water to ice, and prevents damage taken from magma blocks.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_FROST_WALKER;
/// Increases damage to sea creatures.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_IMPALING;
/// Allows shooting a bow without using up any arrows.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_INFINITY;
/// Increases knockback dealt when attacking a LivingEntity.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_KNOCKBACK;
/// Increases amount of loot dropped when slaying an LivingEntity.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_LOOTING;
/// Automatically returns the projectile to the thrower upon landing.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_LOYALTY;
/// Increases chance of catching valuable items when fishing.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_LUCK_OF_THE_SEA;
/// Increases chance of fish biting your hook while fishing.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_LURE;
/// Repairs item durability through gaining experience. Tools need to be held in your hand to be repaired.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_MENDING;
/// Allows multiple projectiles to be sent by a single projectile item.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_MULTISHOT;
/// Allows arrows fired from a crossbow to pierce through multiplie entities.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_PIERCING;
/// Increases damage inflicted by projectiles.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_POWER;
/// Significantly reduces damage from projectiles.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_PROJECTILE_PROTECTION;
/// Moderately reduces damage taken against all types of damage, including from attacks, fire, lava, and falling.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_PROTECTION;
/// Increases knockback dealt to victim hit by projectile.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_PUNCH;
/// Reduces time required to reload a crossbow.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_QUICK_CHARGE;
/// Extends how long you can breathe underwater.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_RESPIRATION;
/// Propels you forward when you throw a trident.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_RIPTIDE;
/// Increases damage to alive entities.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_SHARPNESS;
/// When mining a block, the dropped item will be the block itself instead of its regular drops.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_SILK_TOUCH;
/// Increases damage to undead mobs.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_SMITE;
/// Increases movement speed on soul sand and soul soil.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_SOUL_SPEED;
/// Increases damage to sweep attacks.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_SWEEPING;
/// Inflicts damage upon the attacker.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_THORNS;
/// Decreases chance of item taking durability damage.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_UNBREAKING;
/// Prevents the cursed item from being dropped upon death.
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_VANISHING_CURSE;

struct Enchant {
    const struct EnchantmentType type;
    int level;
};

void enchants_destroy(struct Enchant *enchants);

struct EnchantmentTarget enchantment_type_get_enchantment_target(struct EnchantmentType *enchantment);

#endif /* enchantment_type_h */
