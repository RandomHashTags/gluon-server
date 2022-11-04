//
//  enchantment.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef enchantment_h
#define enchantment_h

enum Enchantment {
    ARROW_DAMAGE,
    ARROW_KNOCKBACK,
    ARROW_FIRE,
    ARROW_INFINITE,
    DAMAGE_ALL,
    DAMAGE_ARTHROPODS,
    DAMAGE_UNDEAD,
    DEPTH_STRIDER,
    DIG_SPEED,
    DURABILITY,
    FIRE_ASPECT,
    KNOCKBACK,
    LOOT_BONUS_BLOCKS,
    LOOT_BONUS_MOBS,
    LUCK,
    LURE,
    OXYGEN,
    PROTECTION_ENVIRONMENTAL,
    PROTECTION_FIRE,
    PROTECTION_FALL,
    PROTECTION_EXPLOSIONS,
    PROTECTION_PROJECTILE,
    SILK_TOUCH,
    THORNS,
    WATER_WORKER
};

struct Enchant {
    const enum Enchantment type;
    int level;
};

#endif /* enchantment_h */
