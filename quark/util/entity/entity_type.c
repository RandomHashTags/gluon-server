//
//  entity_type.c
//  quark
//
//  Created by Evan Anderson on 11/10/22.
//

#include "entity_type.h"
#include "../../utilities.h"

int entity_type_get_no_damage_ticks_maximum(struct EntityType entity_type) {
    return TICKS_PER_SECOND;
}

int entity_type_get_fire_ticks_maximum(struct EntityType entity_type) {
    return TICKS_PER_SECOND;
}

struct EntityType ENTITY_TYPE_MINECRAFT_AREA_EFFECT_CLOUD = { "minecraft.area_effect_cloud" };
struct EntityType ENTITY_TYPE_MINECRAFT_ARMOR_STAND =       { "minecraft.armor_stand" };
struct EntityType ENTITY_TYPE_MINECRAFT_ARROW =             { "minecraft.arrow" };
struct EntityType ENTITY_TYPE_MINECRAFT_ARROW_SPECTRAL =    { "minecraft.arrow_spectral" };

struct EntityType ENTITY_TYPE_MINECRAFT_BAT =               { "minecraft.bat" };
struct EntityType ENTITY_TYPE_MINECRAFT_BEE =               { "minecraft.bee" };
struct EntityType ENTITY_TYPE_MINECRAFT_BLAZE =             { "minecraft.blaze" };
struct EntityType ENTITY_TYPE_MINECRAFT_BOAT =              { "minecraft.boat" };

struct EntityType ENTITY_TYPE_MINECRAFT_CAT =               { "minecraft.cat" };
struct EntityType ENTITY_TYPE_MINECRAFT_CAVE_SPIDER =       { "minecraft.cave_spider" };
struct EntityType ENTITY_TYPE_MINECRAFT_CHICKEN =           { "minecraft.chicken" };
struct EntityType ENTITY_TYPE_MINECRAFT_COD =               { "minecraft.cod" };
struct EntityType ENTITY_TYPE_MINECRAFT_COW =               { "minecraft.cow" };
struct EntityType ENTITY_TYPE_MINECRAFT_CREEPER =           { "minecraft.creeper" };

struct EntityType ENTITY_TYPE_MINECRAFT_DOLPHIN =           { "minecraft.dolphin" };
struct EntityType ENTITY_TYPE_MINECRAFT_DONKEY =            { "minecraft.donkey" };
struct EntityType ENTITY_TYPE_MINECRAFT_DRAGON_FIREBALL =   { "minecraft.dragon_fireball" };
struct EntityType ENTITY_TYPE_MINECRAFT_DROPPED_ITEM =      { "minecraft.dropped_item" };
struct EntityType ENTITY_TYPE_MINECRAFT_DROWNED =           { "minecraft.drowned" };

struct EntityType ENTITY_TYPE_MINECRAFT_EGG =               { "minecraft.egg" };
struct EntityType ENTITY_TYPE_MINECRAFT_ELDER_GUARDIAN =    { "minecraft.elder_guardian" };
struct EntityType ENTITY_TYPE_MINECRAFT_END_CRYSTAL =       { "minecraft.end_crystal" };
struct EntityType ENTITY_TYPE_MINECRAFT_ENDER_DRAGON =      { "minecraft.ender_dragon" };
struct EntityType ENTITY_TYPE_MINECRAFT_ENDER_PEARL =       { "minecraft.ender_pearl" };
struct EntityType ENTITY_TYPE_MINECRAFT_ENDERMAN =          { "minecraft.enderman" };
struct EntityType ENTITY_TYPE_MINECRAFT_ENDERMITE =         { "minecraft.endermite" };
struct EntityType ENTITY_TYPE_MINECRAFT_EVOKER =            { "minecraft.evoker" };
struct EntityType ENTITY_TYPE_MINECRAFT_EVOKER_FANGS =      { "minecraft.evoker_fangs" };
struct EntityType ENTITY_TYPE_MINECRAFT_EXPERIENCE_BOTTLE = { "minecraft.experience_bottle" };
struct EntityType ENTITY_TYPE_MINECRAFT_EXPERIENCE_ORB =    { "minecraft.experience_orb" };
struct EntityType ENTITY_TYPE_MINECRAFT_EYE_OF_ENDER =      { "minecraft.eye_of_ender" };

struct EntityType ENTITY_TYPE_MINECRAFT_FALLING_BLOCK =     { "minecraft.falling_block" };
struct EntityType ENTITY_TYPE_MINECRAFT_FIREBALL =          { "minecraft.fireball" };
struct EntityType ENTITY_TYPE_MINECRAFT_FIREWORK_ROCKET =   { "minecraft.firework_rocket" };
struct EntityType ENTITY_TYPE_MINECRAFT_FISHING_BOBBER =    { "minecraft.fishing_bobber" };
struct EntityType ENTITY_TYPE_MINECRAFT_FOX =               { "minecraft.fox" };

struct EntityType ENTITY_TYPE_MINECRAFT_GHAST =             { "minecraft.ghast" };
struct EntityType ENTITY_TYPE_MINECRAFT_GIANT =             { "minecraft.giant" };
struct EntityType ENTITY_TYPE_MINECRAFT_GUARDIAN =          { "minecraft.guardian" };

struct EntityType ENTITY_TYPE_MINECRAFT_HOGLIN =            { "minecraft.hoglin" };
struct EntityType ENTITY_TYPE_MINECRAFT_HORSE =             { "minecraft.horse" };
struct EntityType ENTITY_TYPE_MINECRAFT_HUSK =              { "minecraft.husk" };

struct EntityType ENTITY_TYPE_MINECRAFT_ILLUSIONER =        { "minecraft.illusioner" };
struct EntityType ENTITY_TYPE_MINECRAFT_IRON_GOLEM =        { "minecraft.iron_golem" };
struct EntityType ENTITY_TYPE_MINECRAFT_ITEM_FRAME =        { "minecraft.item_frame" };

struct EntityType ENTITY_TYPE_MINECRAFT_LEASH_KNOT =        { "minecraft.leash_knot" };
struct EntityType ENTITY_TYPE_MINECRAFT_LIGHTNING_BOLT =    { "minecraft.lightning_bolt" };
struct EntityType ENTITY_TYPE_MINECRAFT_LLAMA =             { "minecraft.llama" };
struct EntityType ENTITY_TYPE_MINECRAFT_LLAMA_SPIT =        { "minecraft.llama_spit" };
struct EntityType ENTITY_TYPE_MINECRAFT_LLAMA_TRADER =      { "minecraft.llama_trader" };

struct EntityType ENTITY_TYPE_MINECRAFT_MAGMA_CUBE =        { "minecraft.magma_cube" };
struct EntityType ENTITY_TYPE_MINECRAFT_MINECART =          { "minecraft.minecart" };
struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_CHEST =    { "minecraft.minecart_chest" };
struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_COMMAND =  { "minecraft.minecart_command" };
struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_FURNACE =  { "minecraft.minecart_furnance" };
struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_HOPPER =   { "minecraft.minecart_hopper" };
struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_SPAWNER =  { "minecraft.minecart_spawner" };
struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_TNT =      { "minecraft.minecart_tnt" };
struct EntityType ENTITY_TYPE_MINECRAFT_MOOSHROOM =         { "minecraft.mooshroom" };
struct EntityType ENTITY_TYPE_MINECRAFT_MULE =              { "minecraft.mule" };
    
struct EntityType ENTITY_TYPE_MINECRAFT_OCELOT =            { "minecraft.ocelot" };

struct EntityType ENTITY_TYPE_MINECRAFT_PAINTING =          { "minecraft.painting" };
struct EntityType ENTITY_TYPE_MINECRAFT_PANDA =             { "minecraft.panda" };
struct EntityType ENTITY_TYPE_MINECRAFT_PARROT =            { "minecraft.parrot" };
struct EntityType ENTITY_TYPE_MINECRAFT_PHANTOM =           { "minecraft.phantom" };
struct EntityType ENTITY_TYPE_MINECRAFT_PIG =               { "minecraft.pig" };
struct EntityType ENTITY_TYPE_MINECRAFT_PIGLIN =            { "minecraft.piglin" };
struct EntityType ENTITY_TYPE_MINECRAFT_PIGLIN_BRUTE =      { "minecraft.piglin_brute" };
struct EntityType ENTITY_TYPE_MINECRAFT_PILLAGER =          { "minecraft.pillager" };
struct EntityType ENTITY_TYPE_MINECRAFT_PLAYER =            { "minecraft.player" };
struct EntityType ENTITY_TYPE_MINECRAFT_POLAR_BEAR =        { "minecraft.polar_bear" };
struct EntityType ENTITY_TYPE_MINECRAFT_POTION =            { "minecraft.potion" };
struct EntityType ENTITY_TYPE_MINECRAFT_PUFFERFISH =        { "minecraft.pufferfish" };

struct EntityType ENTITY_TYPE_MINECRAFT_RABBIT =            { "minecraft.rabbit" };
struct EntityType ENTITY_TYPE_MINECRAFT_RAVAGER =           { "minecraft.ravager" };

struct EntityType ENTITY_TYPE_MINECRAFT_SALMON =            { "minecraft.salmon" };
struct EntityType ENTITY_TYPE_MINECRAFT_SHEEP =             { "minecraft.sheep" };
struct EntityType ENTITY_TYPE_MINECRAFT_SHULKER =           { "minecraft.shulker" };
struct EntityType ENTITY_TYPE_MINECRAFT_SHULKER_BULLET  =   { "minecraft.shulker_bullet" };
struct EntityType ENTITY_TYPE_MINECRAFT_SILVERFISH =        { "minecraft.silverfish" };
struct EntityType ENTITY_TYPE_MINECRAFT_SKELETON =          { "minecraft.skeleton" };
struct EntityType ENTITY_TYPE_MINECRAFT_SKELETON_HORSE =    { "minecraft.skeleton_horse" };
struct EntityType ENTITY_TYPE_MINECRAFT_SLIME =             { "minecraft.slime" };
struct EntityType ENTITY_TYPE_MINECRAFT_SNOW_GOLEM =        { "minecraft.snow_golem" };
struct EntityType ENTITY_TYPE_MINECRAFT_SNOWBALL =          { "minecraft.snowball" };
struct EntityType ENTITY_TYPE_MINECRAFT_SPIDER =            { "minecraft.spider" };
struct EntityType ENTITY_TYPE_MINECRAFT_SQUID =             { "minecraft.squid" };
struct EntityType ENTITY_TYPE_MINECRAFT_STRAY =             { "minecraft.stray" };
struct EntityType ENTITY_TYPE_MINECRAFT_STRIDER =           { "minecraft.strider" };

struct EntityType ENTITY_TYPE_MINECRAFT_TNT =               { "minecraft.tnt" };
struct EntityType ENTITY_TYPE_MINECRAFT_TRIDENT =           { "minecraft.trident" };
struct EntityType ENTITY_TYPE_MINECRAFT_TROPICAL_FISH =     { "minecraft.tropical_fish" };
struct EntityType ENTITY_TYPE_MINECRAFT_TURTLE =            { "minecraft.turtle" };

struct EntityType ENTITY_TYPE_MINECRAFT_VEX =               { "minecraft.vex" };
struct EntityType ENTITY_TYPE_MINECRAFT_VILLAGER =          { "minecraft.villager" };
struct EntityType ENTITY_TYPE_MINECRAFT_VINDICATOR =        { "minecraft.vindicator" };

struct EntityType ENTITY_TYPE_MINECRAFT_WANDERING_TRADER =  { "minecraft.wandering_trader" };
struct EntityType ENTITY_TYPE_MINECRAFT_WITCH =             { "minecraft.witch" };
struct EntityType ENTITY_TYPE_MINECRAFT_WITHER =            { "minecraft.wither" };
struct EntityType ENTITY_TYPE_MINECRAFT_WITHER_SKELETON =   { "minecraft.wither_skeleton" };
struct EntityType ENTITY_TYPE_MINECRAFT_WITHER_SKULL =      { "minecraft.wither_skull" };
struct EntityType ENTITY_TYPE_MINECRAFT_WOLF =              { "minecraft.wolf" };
    
struct EntityType ENTITY_TYPE_MINECRAFT_ZOGLIN =            { "minecraft.zoglin" };
struct EntityType ENTITY_TYPE_MINECRAFT_ZOMBIE =            { "minecraft.zombie" };
struct EntityType ENTITY_TYPE_MINECRAFT_ZOMBIE_HORSE =      { "minecraft.zombie_horse" };
struct EntityType ENTITY_TYPE_MINECRAFT_ZOMBIE_VILLAGER =   { "minecraft.zombie_villager" };
struct EntityType ENTITY_TYPE_MINECRAFT_ZOMBIFIED_PIGLIN =  { "minecraft.zombified_piglin" };
