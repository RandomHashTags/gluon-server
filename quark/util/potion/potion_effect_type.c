//
//  potion_effect_type.c
//  quark
//
//  Created by Evan Anderson on 11/11/22.
//

#include "potion_effect_type.h"

char *potion_effect_type_get_name(enum PotionEffectType type) {
    switch (type) {
        case POTION_EFFECT_TYPE_ABSORPTION: return "Absorption";
        case POTION_EFFECT_TYPE_BAD_OMEN: return "Bad Omen";
        case POTION_EFFECT_TYPE_BLINDNESS: return "Blindness";
        case POTION_EFFECT_TYPE_CONDUIT_POWER: return "Conduit Power";
        case POTION_EFFECT_TYPE_CONFUSION: return "Confusion";
        case POTION_EFFECT_TYPE_DAMAGE_RESISTANCE: return "Resistance";
        case POTION_EFFECT_TYPE_DARKNESS: return "Darkness";
        case POTION_EFFECT_TYPE_DOLPHINS_GRACE: return "Dolphins Grace";
        case POTION_EFFECT_TYPE_FAST_DIGGING: return "Haste";
        case POTION_EFFECT_TYPE_FIRE_RESISTANCE: return "Fire Resistance";
        case POTION_EFFECT_TYPE_GLOWING: return "Glowing";
        case POTION_EFFECT_TYPE_HARM: return "Instant Damage";
        case POTION_EFFECT_TYPE_HEAL: return "Instant Health";
        case POTION_EFFECT_TYPE_HEALTH_BOOST: return "Health Boost";
        case POTION_EFFECT_TYPE_HERO_OF_THE_VILLAGE: return "Hero of the Village";
        case POTION_EFFECT_TYPE_HUNGER: return "Hunger";
        case POTION_EFFECT_TYPE_INCREASE_DAMAGE: return "Strength";
        case POTION_EFFECT_TYPE_INVISIBILITY: return "Invisibility";
        case POTION_EFFECT_TYPE_JUMP: return "Jump";
        case POTION_EFFECT_TYPE_LEVITATION: return "Levitation";
        case POTION_EFFECT_TYPE_LUCK: return "Lucky";
        case POTION_EFFECT_TYPE_NIGHT_VISION: return "Night Vision";
        case POTION_EFFECT_TYPE_POISON: return "Poison";
        case POTION_EFFECT_TYPE_REGENERATION: return "Regeneration";
        case POTION_EFFECT_TYPE_SATURATION: return "Saturation";
        case POTION_EFFECT_TYPE_SLOW: return "Slowness";
        case POTION_EFFECT_TYPE_SLOW_DIGGING: return "Mining Fatigue";
        case POTION_EFFECT_TYPE_SLOW_FALLING: return "Slow Falling";
        case POTION_EFFECT_TYPE_SPEED: return "Speed";
        case POTION_EFFECT_TYPE_UNLUCK: return "Unlucky";
        case POTION_EFFECT_TYPE_WATER_BREATHING: return "Water Breathing";
        case POTION_EFFECT_TYPE_WEAKNESS: return "Weakness";
        case POTION_EFFECT_TYPE_WITHER: return "Wither";
        default: return "Unknown PotionEffectType name";
    }
}
_Bool potion_effect_type_is_instant(enum PotionEffectType type) {
    switch (type) {
        case POTION_EFFECT_TYPE_HARM:
        case POTION_EFFECT_TYPE_HEAL:
        case POTION_EFFECT_TYPE_SATURATION:
            return 1;
        default:
            return 0;
    }
}
