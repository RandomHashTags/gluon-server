//
//  potion_effect_type.c
//  quark
//
//  Created by Evan Anderson on 11/11/22.
//

#include <stdio.h>
#include "potion_effect_type.h"

char *potion_effect_type_get_name(struct PotionEffectType type) {
    /*switch (type) {
        case POTION_EFFECT_TYPE_MINECRAFT_ABSORPTION: return "Absorption";
        case POTION_EFFECT_TYPE_MINECRAFT_BAD_OMEN: return "Bad Omen";
        case POTION_EFFECT_TYPE_MINECRAFT_BLINDNESS: return "Blindness";
        case POTION_EFFECT_TYPE_MINECRAFT_CONDUIT_POWER: return "Conduit Power";
        case POTION_EFFECT_TYPE_MINECRAFT_CONFUSION: return "Confusion";
        case POTION_EFFECT_TYPE_MINECRAFT_DAMAGE_RESISTANCE: return "Resistance";
        case POTION_EFFECT_TYPE_MINECRAFT_DARKNESS: return "Darkness";
        case POTION_EFFECT_TYPE_MINECRAFT_DOLPHINS_GRACE: return "Dolphins Grace";
        case POTION_EFFECT_TYPE_MINECRAFT_HASTE: return "Haste";
        case POTION_EFFECT_TYPE_MINECRAFT_FIRE_RESISTANCE: return "Fire Resistance";
        case POTION_EFFECT_TYPE_MINECRAFT_GLOWING: return "Glowing";
        case POTION_EFFECT_TYPE_MINECRAFT_HARM: return "Instant Damage";
        case POTION_EFFECT_TYPE_MINECRAFT_HEAL: return "Instant Health";
        case POTION_EFFECT_TYPE_MINECRAFT_HEALTH_BOOST: return "Health Boost";
        case POTION_EFFECT_TYPE_MINECRAFT_HERO_OF_THE_VILLAGE: return "Hero of the Village";
        case POTION_EFFECT_TYPE_MINECRAFT_HUNGER: return "Hunger";
        case POTION_EFFECT_TYPE_MINECRAFT_STRENGTH: return "Strength";
        case POTION_EFFECT_TYPE_MINECRAFT_INVISIBILITY: return "Invisibility";
        case POTION_EFFECT_TYPE_MINECRAFT_JUMP_BOOST: return "Jump";
        case POTION_EFFECT_TYPE_MINECRAFT_LEVITATION: return "Levitation";
        case POTION_EFFECT_TYPE_MINECRAFT_LUCK: return "Lucky";
        case POTION_EFFECT_TYPE_MINECRAFT_NIGHT_VISION: return "Night Vision";
        case POTION_EFFECT_TYPE_MINECRAFT_POISON: return "Poison";
        case POTION_EFFECT_TYPE_MINECRAFT_REGENERATION: return "Regeneration";
        case POTION_EFFECT_TYPE_MINECRAFT_SATURATION: return "Saturation";
        case POTION_EFFECT_TYPE_MINECRAFT_SLOWNESS: return "Slowness";
        case POTION_EFFECT_TYPE_MINECRAFT_MINING_FATIGUE: return "Mining Fatigue";
        case POTION_EFFECT_TYPE_MINECRAFT_SLOW_FALLING: return "Slow Falling";
        case POTION_EFFECT_TYPE_MINECRAFT_SPEED: return "Speed";
        case POTION_EFFECT_TYPE_MINECRAFT_UNLUCK: return "Unlucky";
        case POTION_EFFECT_TYPE_MINECRAFT_WATER_BREATHING: return "Water Breathing";
        case POTION_EFFECT_TYPE_MINECRAFT_WEAKNESS: return "Weakness";
        case POTION_EFFECT_TYPE_MINECRAFT_WITHER: return "Wither";
        default: return "Unknown PotionEffectType name";
    }*/
    return NULL;
}
_Bool potion_effect_type_is_instant(struct PotionEffectType type) {
    /*switch (type) {
        case POTION_EFFECT_TYPE_MINECRAFT_HARM:
        case POTION_EFFECT_TYPE_MINECRAFT_HEAL:
        case POTION_EFFECT_TYPE_MINECRAFT_SATURATION:
            return 1;
        default:
            return 0;
    }*/
    return 0;
}

struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_ABSORPTION =          { .identifier = "minecraft.absorption" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_BAD_OMEN =            { .identifier = "minecraft.bad_omen" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_BLINDNESS =           { .identifier = "minecraft.blindness" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_CONDUIT_POWER =       { .identifier = "minecraft.conduit_power" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_CONFUSION =           { .identifier = "minecraft.confusion" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_DAMAGE_RESISTANCE =   { .identifier = "minecraft.damage_resistance" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_DARKNESS =            { .identifier = "minecraft.darkness" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_DOLPHINS_GRACE =      { .identifier = "minecraft.dolphins_grace" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_FIRE_RESISTANCE =     { .identifier = "minecraft.fire_resistance" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_GLOWING =             { .identifier = "minecraft.glowing" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HARM =                { .identifier = "minecraft.harm" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HASTE =               { .identifier = "minecraft.haste" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HEAL =                { .identifier = "minecraft.heal" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HEALTH_BOOST =        { .identifier = "minecraft.health_boost" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HERO_OF_THE_VILLAGE = { .identifier = "minecraft.hero_of_the_village" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HUNGER =              { .identifier = "minecraft.hunger" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_INVISIBILITY =        { .identifier = "minecraft.invisibility" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_JUMP_BOOST =          { .identifier = "minecraft.jump" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_LEVITATION =          { .identifier = "minecraft.levitation" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_LUCK =                { .identifier = "minecraft.luck" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_MINING_FATIGUE =      { .identifier = "minecraft.mining_fatigue" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_NIGHT_VISION =        { .identifier = "minecraft.night_vision" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_POISON =              { .identifier = "minecraft.poison" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_REGENERATION =        { .identifier = "minecraft.regeneration" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_SATURATION =          { .identifier = "minecraft.saturation" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_SLOWNESS =            { .identifier = "minecraft.slowness" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_SLOW_FALLING =        { .identifier = "minecraft.slow_falling" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_SPEED =               { .identifier = "minecraft.speed" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_STRENGTH =            { .identifier = "minecraft.strength" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_UNLUCK =              { .identifier = "minecraft.unluck" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_WATER_BREATHING =     { .identifier = "minecraft.water_breathing" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_WEAKNESS =            { .identifier = "minecraft.weakness" };
struct PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_WITHER =              { .identifier = "minecraft.wither" };
