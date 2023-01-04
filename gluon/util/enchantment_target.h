//
//  enchantment_target.h
//  gluon
//
//  Created by Evan Anderson on 11/12/22.
//

#ifndef enchantment_target_h
#define enchantment_target_h

struct EnchantmentTarget {
    const char *identifier;
};

extern struct EnchantmentTarget ENCHANTMENT_TARGET_MINECRAFT_ALL;
extern struct EnchantmentTarget ENCHANTMENT_TARGET_MINECRAFT_ARMOR_FEET;
extern struct EnchantmentTarget ENCHANTMENT_TARGET_MINECRAFT_ARMOR_HEAD;
extern struct EnchantmentTarget ENCHANTMENT_TARGET_MINECRAFT_ARMOR_LEGS;
extern struct EnchantmentTarget ENCHANTMENT_TARGET_MINECRAFT_ARMOR_TORSO;
extern struct EnchantmentTarget ENCHANTMENT_TARGET_MINECRAFT_BOW;
extern struct EnchantmentTarget ENCHANTMENT_TARGET_MINECRAFT_CROSSBOW;
extern struct EnchantmentTarget ENCHANTMENT_TARGET_MINECRAFT_FISHING_ROD;
extern struct EnchantmentTarget ENCHANTMENT_TARGET_MINECRAFT_TRIDENT;
extern struct EnchantmentTarget ENCHANTMENT_TARGET_MINECRAFT_WEAPON;

#endif /* enchantment_target_h */
