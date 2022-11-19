//
//  entity_type.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef entity_type_h
#define entity_type_h

struct EntityType {
    const char *identifier;
    unsigned short no_damage_ticks_maximum;
    unsigned short fire_ticks_maximum;
};

struct EntityType *entity_type_create(const char *identifier, unsigned short no_damage_ticks_maximum, unsigned short fire_ticks_maximum);
void entity_type_destroy(struct EntityType *type);

extern struct EntityType ENTITY_TYPE_MINECRAFT_AREA_EFFECT_CLOUD;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ARMOR_STAND;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ARROW;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ARROW_SPECTRAL;
    
extern struct EntityType ENTITY_TYPE_MINECRAFT_BAT;
extern struct EntityType ENTITY_TYPE_MINECRAFT_BEE;
extern struct EntityType ENTITY_TYPE_MINECRAFT_BLAZE;
extern struct EntityType ENTITY_TYPE_MINECRAFT_BOAT;
    
extern struct EntityType ENTITY_TYPE_MINECRAFT_CAT;
extern struct EntityType ENTITY_TYPE_MINECRAFT_CAVE_SPIDER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_CHICKEN;
extern struct EntityType ENTITY_TYPE_MINECRAFT_COD;
extern struct EntityType ENTITY_TYPE_MINECRAFT_COW;
extern struct EntityType ENTITY_TYPE_MINECRAFT_CREEPER;
    
extern struct EntityType ENTITY_TYPE_MINECRAFT_DOLPHIN;
extern struct EntityType ENTITY_TYPE_MINECRAFT_DONKEY;
extern struct EntityType ENTITY_TYPE_MINECRAFT_DRAGON_FIREBALL;
extern struct EntityType ENTITY_TYPE_MINECRAFT_DROPPED_ITEM;
extern struct EntityType ENTITY_TYPE_MINECRAFT_DROWNED;
    
extern struct EntityType ENTITY_TYPE_MINECRAFT_EGG;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ELDER_GUARDIAN;
extern struct EntityType ENTITY_TYPE_MINECRAFT_END_CRYSTAL;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ENDER_DRAGON;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ENDER_PEARL;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ENDERMAN;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ENDERMITE;
extern struct EntityType ENTITY_TYPE_MINECRAFT_EVOKER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_EVOKER_FANGS;
extern struct EntityType ENTITY_TYPE_MINECRAFT_EXPERIENCE_BOTTLE;
extern struct EntityType ENTITY_TYPE_MINECRAFT_EXPERIENCE_ORB;
extern struct EntityType ENTITY_TYPE_MINECRAFT_EYE_OF_ENDER;

extern struct EntityType ENTITY_TYPE_MINECRAFT_FALLING_BLOCK;
extern struct EntityType ENTITY_TYPE_MINECRAFT_FIREBALL;
extern struct EntityType ENTITY_TYPE_MINECRAFT_FIREWORK_ROCKET;
extern struct EntityType ENTITY_TYPE_MINECRAFT_FISHING_BOBBER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_FOX;

extern struct EntityType ENTITY_TYPE_MINECRAFT_GHAST;
extern struct EntityType ENTITY_TYPE_MINECRAFT_GIANT;
extern struct EntityType ENTITY_TYPE_MINECRAFT_GUARDIAN;

extern struct EntityType ENTITY_TYPE_MINECRAFT_HOGLIN;
extern struct EntityType ENTITY_TYPE_MINECRAFT_HORSE;
extern struct EntityType ENTITY_TYPE_MINECRAFT_HUSK;
    
extern struct EntityType ENTITY_TYPE_MINECRAFT_ILLUSIONER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_IRON_GOLEM;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ITEM_FRAME;

extern struct EntityType ENTITY_TYPE_MINECRAFT_LEASH_KNOT;
extern struct EntityType ENTITY_TYPE_MINECRAFT_LIGHTNING_BOLT;
extern struct EntityType ENTITY_TYPE_MINECRAFT_LLAMA;
extern struct EntityType ENTITY_TYPE_MINECRAFT_LLAMA_SPIT;
extern struct EntityType ENTITY_TYPE_MINECRAFT_LLAMA_TRADER;

extern struct EntityType ENTITY_TYPE_MINECRAFT_MAGMA_CUBE;
extern struct EntityType ENTITY_TYPE_MINECRAFT_MINECART;
extern struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_CHEST;
extern struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_COMMAND;
extern struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_FURNACE;
extern struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_HOPPER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_SPAWNER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_MINECART_TNT;
extern struct EntityType ENTITY_TYPE_MINECRAFT_MOOSHROOM;
extern struct EntityType ENTITY_TYPE_MINECRAFT_MULE;
    
extern struct EntityType ENTITY_TYPE_MINECRAFT_OCELOT;
    
extern struct EntityType ENTITY_TYPE_MINECRAFT_PAINTING;
extern struct EntityType ENTITY_TYPE_MINECRAFT_PANDA;
extern struct EntityType ENTITY_TYPE_MINECRAFT_PARROT;
extern struct EntityType ENTITY_TYPE_MINECRAFT_PHANTOM;
extern struct EntityType ENTITY_TYPE_MINECRAFT_PIG;
extern struct EntityType ENTITY_TYPE_MINECRAFT_PIGLIN;
extern struct EntityType ENTITY_TYPE_MINECRAFT_PIGLIN_BRUTE;
extern struct EntityType ENTITY_TYPE_MINECRAFT_PILLAGER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_PLAYER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_POLAR_BEAR;
extern struct EntityType ENTITY_TYPE_MINECRAFT_POTION;
extern struct EntityType ENTITY_TYPE_MINECRAFT_PUFFERFISH;

extern struct EntityType ENTITY_TYPE_MINECRAFT_RABBIT;
extern struct EntityType ENTITY_TYPE_MINECRAFT_RAVAGER;

extern struct EntityType ENTITY_TYPE_MINECRAFT_SALMON;
extern struct EntityType ENTITY_TYPE_MINECRAFT_SHEEP;
extern struct EntityType ENTITY_TYPE_MINECRAFT_SHULKER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_SHULKER_BULLET;
extern struct EntityType ENTITY_TYPE_MINECRAFT_SILVERFISH;
extern struct EntityType ENTITY_TYPE_MINECRAFT_SKELETON;
extern struct EntityType ENTITY_TYPE_MINECRAFT_SKELETON_HORSE;
extern struct EntityType ENTITY_TYPE_MINECRAFT_SLIME;
extern struct EntityType ENTITY_TYPE_MINECRAFT_SNOW_GOLEM;
extern struct EntityType ENTITY_TYPE_MINECRAFT_SNOWBALL;
extern struct EntityType ENTITY_TYPE_MINECRAFT_SPIDER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_SQUID;
extern struct EntityType ENTITY_TYPE_MINECRAFT_STRAY;
extern struct EntityType ENTITY_TYPE_MINECRAFT_STRIDER;

extern struct EntityType ENTITY_TYPE_MINECRAFT_TNT;
extern struct EntityType ENTITY_TYPE_MINECRAFT_TRIDENT;
extern struct EntityType ENTITY_TYPE_MINECRAFT_TROPICAL_FISH;
extern struct EntityType ENTITY_TYPE_MINECRAFT_TURTLE;

extern struct EntityType ENTITY_TYPE_MINECRAFT_VEX;
extern struct EntityType ENTITY_TYPE_MINECRAFT_VILLAGER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_VINDICATOR;

extern struct EntityType ENTITY_TYPE_MINECRAFT_WANDERING_TRADER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_WITCH;
extern struct EntityType ENTITY_TYPE_MINECRAFT_WITHER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_WITHER_SKELETON;
extern struct EntityType ENTITY_TYPE_MINECRAFT_WITHER_SKULL;
extern struct EntityType ENTITY_TYPE_MINECRAFT_WOLF;
    
extern struct EntityType ENTITY_TYPE_MINECRAFT_ZOGLIN;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ZOMBIE;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ZOMBIE_HORSE;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ZOMBIE_VILLAGER;
extern struct EntityType ENTITY_TYPE_MINECRAFT_ZOMBIFIED_PIGLIN;

#endif /* entity_type_h */
