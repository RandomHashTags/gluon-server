//
//  world.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "../../utilities.h"

struct World *world_create(enum MinecraftVersion version, const long seed, const char *world_name, struct Difficulty *difficulty) {
    struct World *world = malloc(sizeof(struct World));
    if (!world) {
        printf("failed to allocate memory for a World\n");
        return NULL;
    }
    const unsigned int players_maximum = SERVER->player_count_maximum;
    struct PlayerConnection **players = malloc(players_maximum * sizeof(struct PlayerConnection *));
    if (!players) {
        free(world);
        printf("failed to allocate memory for a World players\n");
        return NULL;
    }
    
    const unsigned int chunks_loaded_count_maximum = 16 * 16;
    memcpy((unsigned int *) &world->chunks_loaded_count_maximum, &chunks_loaded_count_maximum, sizeof(unsigned int));
    struct Chunk **chunks_loaded = malloc(chunks_loaded_count_maximum * sizeof(struct Chunk *));
    if (!chunks_loaded) {
        free(world);
        free(players);
        printf("failed to allocate memory for a World chunks_loaded\n");
        return NULL;
    }
    world->chunks_loaded = chunks_loaded;
    world->chunks_loaded_count = 0;
    
    const float location_x = 0, location_y = 10, location_z = 0;
    struct Chunk *chunk = world_get_or_load_chunk(world, (long) location_x / 16, (long) location_z / 16);
    if (!chunk) {
        free(world);
        free(players);
        free(chunks_loaded);
        return NULL;
    }
    struct Location *spawn_location = location_create(world, chunk, location_x, location_y, location_z, 90, 0);
    if (!spawn_location) {
        free(world);
        free(players);
        free(chunks_loaded);
        printf("failed to allocate a World spawn_location\n");
        return NULL;
    }
    
    const char *target_world_name = malloc_string(world_name);
    if (!target_world_name) {
        free(world);
        free(players);
        free(chunks_loaded);
        free(spawn_location);
        printf("failed to allocate memory for a QuarkServer target_world_name\n");
        return NULL;
    }
    
    world->version = version;
    world->name = target_world_name;
    memcpy((long *) &world->seed, &seed, sizeof(seed));
    world->spawn_location = spawn_location;
    world->player_count = 0;
    world->players = players;
    world->difficulty = difficulty;
    printf("created world at address %p with seed %ld\n", world, seed);
    return world;
}
void world_destroy(struct World *world) {
    const unsigned int player_count = world->player_count;
    struct PlayerConnection **connections = world->players;
    for (unsigned int i = 0; i < player_count; i++) {
        struct PlayerConnection *connection = connections[i];
        // TODO: kick player
        player_connection_destroy(connection);
    }
    free(connections);
    
    const unsigned int living_entity_count = world->living_entity_count;
    struct LivingEntity **living_entities = world->living_entities;
    for (unsigned int i = 0; i < living_entity_count; i++) {
        struct LivingEntity *living_entity = living_entities[i];
        living_entity_destroy(living_entity);
    }
    free(living_entities);
    
    const unsigned int entity_count = world->entity_count;
    struct Entity **entities = world->entities;
    for (unsigned int i = 0; i < entity_count; i++) {
        struct Entity *entity = entities[i];
        entity_destroy(entity);
    }
    free(entities);
    
    const unsigned int chunks_loaded_count = world->chunks_loaded_count;
    struct Chunk **chunks = world->chunks_loaded;
    for (unsigned int i = 0; i < chunks_loaded_count; i++) {
        struct Chunk *chunk = chunks[i];
        chunk_destroy(chunk);
    }
    free(chunks);
    
    location_destroy(world->spawn_location);
    free((char *) world->name);
    free(world->difficulty);
    free(world->biomes);
    free(world);
}

void world_tick(struct World *world) {
    printf("world \"%s\" at address %p will be ticked...\n", world->name, world);
    const unsigned int entity_count = world->entity_count;
    struct Entity **entities = world->entities;
    for (unsigned int i = 0; i < entity_count; i++) {
        struct Entity *entity = entities[i];
        entity_tick(entity);
    }
    
    const unsigned int living_entity_count = world->living_entity_count;
    struct LivingEntity **livingEntities = world->living_entities;
    for (unsigned short i = 0; i < living_entity_count; i++) {
        struct LivingEntity *entity = livingEntities[i];
        living_entity_tick(entity);
    }
    
    const unsigned int player_count = SERVER->player_count;
    struct PlayerConnection **players = world->players;
    for (unsigned int i = 0; i < player_count; i++) {
        printf("ticking player #%d, ", i);
        struct PlayerConnection *connection = players[i];
        printf("with ping %d -> ", connection->ping);
        struct Player *player = connection->player;
        player_tick(player);
        damageable_damage(player->living_entity->damageable, 1);
    }
    printf("finished ticking world \"%s\" at address %p\n", world->name, world);
}

void world_sync_tick_rate_for_entity(struct World *world, struct Entity *entity, const struct EntityType *entity_type) {
    entity->fire_ticks *= TICKS_PER_SECOND_MULTIPLIER;
    entity->fire_ticks_maximum = entity_type->fire_ticks_maximum;
    
    entity->freeze_ticks *= TICKS_PER_SECOND_MULTIPLIER;
    entity->freeze_ticks_maximum = entity_type->freeze_ticks_maximum;
}
void world_sync_tick_rate_for_living_entity(struct World *world, struct LivingEntity *living_entity, const struct EntityType *entity_type, const unsigned short no_damage_ticks_maximum) {
    struct Entity *entity = living_entity->damageable->entity;
    
    living_entity->no_damage_ticks *= TICKS_PER_SECOND_MULTIPLIER;
    living_entity->no_damage_ticks_maximum = no_damage_ticks_maximum;
    
    struct PotionEffect **potion_effects = living_entity->potion_effects;
    const unsigned short potion_effect_count = living_entity->potion_effect_count;
    for (unsigned short i = 0; i < potion_effect_count; i++) {
        struct PotionEffect *potion_effect = potion_effects[i];
        potion_effect->duration *= TICKS_PER_SECOND_MULTIPLIER;
    }
    
    world_sync_tick_rate_for_entity(world, entity, entity_type);
}
void world_sync_tick_rate_for_player(struct World *world, struct PlayerConnection *player, const unsigned short no_damage_ticks_maximum) {
    struct EntityType *entity_type_player = server_get_entity_type("minecraft.player");
    world_sync_tick_rate_for_living_entity(world, player->player->living_entity, entity_type_player, no_damage_ticks_maximum);
}
void world_change_tick_rate(struct World *world, const unsigned short tick_rate) {
    const unsigned int player_count = world->player_count;
    struct PlayerConnection **players = world->players;
    printf("updating tickrate values for %d player(s)...\n", player_count);
    struct EntityType *entity_type_player = server_get_entity_type("minecraft.player");
    const unsigned short maximumPlayerNoDamageTicksMaximum = entity_type_player->no_damage_ticks_maximum;
    for (unsigned int i = 0; i < player_count; i++) {
        struct PlayerConnection *connection = players[i];
        world_sync_tick_rate_for_player(world, connection, maximumPlayerNoDamageTicksMaximum);
    }
    
    const int living_entity_count = world->living_entity_count;
    struct LivingEntity **living_entities = world->living_entities;
    for (unsigned short i = 0; i < living_entity_count; i++) {
        struct LivingEntity *living_entity = living_entities[i];
        const struct EntityType *entity_type = living_entity->damageable->entity->type;
        world_sync_tick_rate_for_living_entity(world, living_entity, entity_type, entity_type->no_damage_ticks_maximum);
    }
}

struct Chunk *world_get_loaded_chunk(struct World *world, const long x, const long z) {
    const unsigned int chunks_loaded_count = world->chunks_loaded_count;
    struct Chunk **chunks = world->chunks_loaded;
    for (unsigned int i = 0; i < chunks_loaded_count; i++) {
        struct Chunk *chunk = chunks[i];
        if (x == chunk->x && z == chunk->z) {
            return chunk;
        }
    }
    return NULL;
}
struct Chunk *world_get_or_load_chunk(struct World *world, const long x, const long z) {
    struct Chunk *chunk = world_get_loaded_chunk(world, x, z);
    const unsigned int chunks_loaded_count = world->chunks_loaded_count;
    if (!chunk && chunks_loaded_count + 1 < world->chunks_loaded_count_maximum) {
        // TODO: try parsing from file
        chunk = chunk_create(world, x, z);
        if (chunk) {
            memcpy(&world->chunks_loaded[chunks_loaded_count], chunk, sizeof(struct Chunk));
            world->chunks_loaded_count += 1;
        }
    }
    if (!chunk) {
        printf("failed to world_get_or_load_chunk\n");
    }
    return chunk;
}
void world_unload_chunk(struct World *world, struct Chunk *chunk) {
    const unsigned int chunks_loaded = world->chunks_loaded_count;
    struct Chunk **chunks = world->chunks_loaded;
    for (unsigned int i = 0; i < chunks_loaded; i++) {
        struct Chunk *targetChunk = chunks[i];
        if (targetChunk == chunk) {
            const int chunk_memory_size = sizeof(struct Chunk);
            chunk_destroy(chunk);
            for (unsigned int j = i; j < chunks_loaded-1; j++) {
                memmove(&chunks[j], &chunks[j+1], chunk_memory_size);
            }
            world->chunks_loaded_count -= 1;
            break;
        }
    }
}
    
void world_player_quit(struct World *world, struct PlayerConnection *connection) {
    const unsigned int player_uuid = connection->player->living_entity->damageable->entity->uuid;
    const unsigned int player_count = world->player_count;
    struct PlayerConnection **players = world->players;
    for (unsigned int i = 0; i < player_count; i++) {
        if (players[i]->player->living_entity->damageable->entity->uuid == player_uuid) {
            for (unsigned int j = i; j < player_count-1; j++) {
                world->players[j] = players[j+1];
            }
            break;
        }
    }
    world->player_count -= 1;
    server_player_quit(connection);
}
void world_player_joined(struct World *world, struct PlayerConnection *connection) {
    struct Player *player = connection->player;
    memcpy(player->living_entity->damageable->entity->location, world->spawn_location, sizeof(struct Location)); // TODO: set player's location to their last location, else world spawn location
    
    const unsigned int player_count = world->player_count;
    world->players[player_count] = connection;
    world->player_count += 1;
    printf("world_player_joined; player connection at address %p joined world at address %p\n", connection, world);
}

struct LivingEntity *world_get_living_entity_from_uuid(const struct World *world, const unsigned int uuid) {
    const unsigned int living_entities_count = world->living_entity_count;
    struct LivingEntity **living_entities = world->living_entities;
    for (unsigned int i = 0; i < living_entities_count; i++) {
        struct LivingEntity *living_entity = living_entities[i];
        if (uuid == living_entity->damageable->entity->uuid) {
            return living_entity;
        }
    }
    struct PlayerConnection *player = world_get_player_connection_from_uuid(world, uuid);
    if (player) {
        return player->player->living_entity;
    }
    printf("world_get_living_entity_from_uuid; world at address %p return NULL for uuid %d\n", world, uuid);
    return NULL;
}
struct PlayerConnection *world_get_player_connection_from_uuid(const struct World *world, const unsigned int uuid) {
    const unsigned int players_count = world->player_count;
    struct PlayerConnection **players = world->players;
    for (unsigned int i = 0; i < players_count; i++) {
        struct PlayerConnection *player = players[i];
        if (uuid == player->player->living_entity->damageable->entity->uuid) {
            return player;
        }
    }
    return NULL;
}
