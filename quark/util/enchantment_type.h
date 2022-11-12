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
/// Reduces damage taken from fire and lava.
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
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_KNOCKBACK;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_LOOTING;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_LOYALTY;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_LUCK_OF_THE_SEA;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_LURE;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_MENDING;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_MULTISHOT;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_PIERCING;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_POWER;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_PROJECTILE_PROTECTION;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_PROTECTION;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_PUNCH;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_QUICK_CHARGE;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_RESPIRATION;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_RIPTIDE;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_SHARPNESS;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_SILK_TOUCH;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_SMITE;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_SOUL_SPEED;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_SWEEPING;
extern struct EnchantmentType ENCHANTMENT_TYPE_MINECRAFT_THORNS;
/// Increases item durability.
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
