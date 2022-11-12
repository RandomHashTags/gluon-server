//
//  potion_effect_type.c
//  quark
//
//  Created by Evan Anderson on 11/11/22.
//

#include <stdio.h>
#include "potion_effect_type.h"

char *potion_effect_type_get_name(PotionEffectType type) {
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
_Bool potion_effect_type_is_instant(PotionEffectType type) {
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

PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_ABSORPTION =          { .identifier = "minecraft.absorption" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_BAD_OMEN =            { .identifier = "minecraft.bad_omen" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_BLINDNESS =           { .identifier = "minecraft.blindness" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_CONDUIT_POWER =       { .identifier = "minecraft.conduit_power" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_CONFUSION =           { .identifier = "minecraft.confusion" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_DAMAGE_RESISTANCE =   { .identifier = "minecraft.damage_resistance" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_DARKNESS =            { .identifier = "minecraft.darkness" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_DOLPHINS_GRACE =      { .identifier = "minecraft.dolphins_grace" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_FIRE_RESISTANCE =     { .identifier = "minecraft.fire_resistance" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_GLOWING =             { .identifier = "minecraft.glowing" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HARM =                { .identifier = "minecraft.harm" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HASTE =               { .identifier = "minecraft.haste" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HEAL =                { .identifier = "minecraft.heal" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HEALTH_BOOST =        { .identifier = "minecraft.health_boost" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HERO_OF_THE_VILLAGE = { .identifier = "minecraft.hero_of_the_village" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_HUNGER =              { .identifier = "minecraft.hunger" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_INVISIBILITY =        { .identifier = "minecraft.invisibility" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_JUMP_BOOST =          { .identifier = "minecraft.jump" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_LEVITATION =          { .identifier = "minecraft.levitation" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_LUCK =                { .identifier = "minecraft.luck" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_MINING_FATIGUE =      { .identifier = "minecraft.mining_fatigue" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_NIGHT_VISION =        { .identifier = "minecraft.night_vision" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_POISON =              { .identifier = "minecraft.poison" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_REGENERATION =        { .identifier = "minecraft.regeneration" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_SATURATION =          { .identifier = "minecraft.saturation" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_SLOWNESS =            { .identifier = "minecraft.slowness" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_SLOW_FALLING =        { .identifier = "minecraft.slow_falling" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_SPEED =               { .identifier = "minecraft.speed" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_STRENGTH =            { .identifier = "minecraft.strength" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_UNLUCK =              { .identifier = "minecraft.unluck" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_WATER_BREATHING =     { .identifier = "minecraft.water_breathing" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_WEAKNESS =            { .identifier = "minecraft.weakness" };
PotionEffectType POTION_EFFECT_TYPE_MINECRAFT_WITHER =              { .identifier = "minecraft.wither" };
