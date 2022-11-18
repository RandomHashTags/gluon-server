//
//  world.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef world_h
#define world_h

#include "biome.h"
#include "chunk.h"
#include "../difficulty.h"
#include "../../minecraft_version.h"
#include "../../network/player_connection.h"

struct World {
    enum MinecraftVersion version;
    const long seed;
    const char *name;
    
    struct Location *spawn_location;
    struct Difficulty *difficulty;
    struct Biome *biomes;
    
    unsigned int chunks_loaded_count;
    const unsigned int chunks_loaded_count_maximum;
    struct Chunk *chunks_loaded;
    
    unsigned int entity_count;
    struct Entity *entities;
    
    unsigned int player_count;
    struct PlayerConnection *players;
    
    unsigned int living_entity_count;
    struct LivingEntity *living_entities;
};

struct World *world_create(enum MinecraftVersion version, const long seed, const char *world_name, struct Difficulty *difficulty);
void world_destroy(struct World *world);

void world_tick(struct World *world);

void world_sync_tick_rate_for_entity(struct World *world, struct Entity *entity, const struct EntityType *entity_type);
void world_sync_tick_rate_for_living_entity(struct World *world, struct LivingEntity *entity, const struct EntityType *type, const unsigned short no_damage_ticks_maximum);
void world_sync_tick_rate_for_player(struct World *world, struct PlayerConnection *player, const unsigned short no_damage_ticks_maximum);
void world_change_tick_rate(struct World *world, const unsigned short tick_rate);

void world_load_chunk(struct World *world, struct Chunk *chunk);
void world_unload_chunk(struct World *world, struct Chunk *chunk);

void world_player_joined(struct World *world, struct PlayerConnection *connection);
void world_player_quit(struct World *world, struct PlayerConnection *connection);

#endif /* world_h */
