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

struct World *world_create(const long seed, const char *world_name, struct Difficulty *difficulty) {
    struct World *world = malloc(sizeof(struct World));
    if (!world) {
        printf("failed to allocate memory for a World\n");
        return NULL;
    }
    const unsigned int players_maximum = SERVER->player_count_maximum;
    struct PlayerConnection *players = malloc(players_maximum * sizeof(struct PlayerConnection));
    if (!players) {
        free(world);
        printf("failed to allocate memory for a World playersPointer\n");
        return 0;
    }
    
    const unsigned int chunks_loaded_count_maximum = 16 * 16;
    memcpy((unsigned int *) &world->chunks_loaded_count_maximum, &chunks_loaded_count_maximum, sizeof(unsigned int));
    struct Chunk *chunks_loaded = malloc(chunks_loaded_count_maximum * sizeof(struct Chunk));
    if (!chunks_loaded) {
        free(world);
        free(players);
        printf("failed to allocate memory for a World chunks_loaded pointer\n");
        return NULL;
    }
    
    const char *target_world_name = malloc(sizeof(*world_name));
    if (!target_world_name) {
        free(world);
        free(players);
        free(chunks_loaded);
        printf("failed to allocate memory for a QuarkServer target_world_name pointer\n");
        return NULL;
    }
    target_world_name = world_name;
    world->name = target_world_name;
    memcpy((long *) &world->seed, &seed, sizeof(seed));
    world->chunks_loaded = chunks_loaded;
    world->chunks_loaded_count = 0;
    world->player_count = 0;
    world->players = players;
    world->difficulty = difficulty;
    return world;
}
void world_destroy(struct World *world) {
    free((char *) world->name);
    free(world->difficulty);
    
    const int player_count = world->player_count;
    struct PlayerConnection *connections = world->players;
    for (int i = 0; i < player_count; i++) {
        struct PlayerConnection *connection = &connections[i];
        // TODO: kick player
        player_connection_destroy(connection);
    }
    free(connections);
    
    const int living_entity_count = world->living_entity_count;
    struct LivingEntity *living_entities = world->living_entities;
    for (int i = 0; i < living_entity_count; i++) {
        struct LivingEntity *living_entity = &living_entities[i];
        living_entity_destroy(living_entity);
    }
    free(living_entities);
    
    const int entity_count = world->entity_count;
    struct Entity *entities = world->entities;
    for (int i = 0; i < entity_count; i++) {
        struct Entity *entity = &entities[i];
        entity_destroy(entity);
    }
    free(entities);
    
    const int chunks_loaded_count = world->chunks_loaded_count;
    struct Chunk *chunks = world->chunks_loaded;
    for (int i = 0; i < chunks_loaded_count; i++) {
        struct Chunk *chunk = &chunks[i];
        chunk_destroy(chunk);
    }
    free(chunks);
    
    free(world);
}

void world_tick(struct World *world) {
    const int entity_count = world->entity_count;
    struct Entity *entities = world->entities;
    for (int i = 0; i < entity_count; i++) {
        struct Entity *entity = &entities[i];
        entity_tick(entity);
    }
    
    const int living_entity_count = world->living_entity_count;
    struct LivingEntity *livingEntities = world->living_entities;
    for (int i = 0; i < living_entity_count; i++) {
        struct LivingEntity *entity = &livingEntities[i];
        living_entity_tick(entity);
    }
    
    const int player_count = SERVER->player_count;
    printf("world \"%s\" will tick %d player(s)...\n", world->name, player_count);
    struct PlayerConnection *players = world->players;
    for (int i = 0; i < player_count; i++) {
        printf("ticking player #%d, ", i);
        struct PlayerConnection *connection = &players[i];
        printf("with ping %d\n", connection->ping);
        struct Player *player = connection->player;
        player_tick(player);
        damageable_damage(player->living_entity->damageable, 1);
    }
    printf("finished ticking world \"%s\"\n", world->name);
}

void world_sync_tick_rate_for_entity(struct World *world, struct Entity *entity, const struct EntityType *entity_type) {
    entity->fire_ticks *= TICKS_PER_SECOND_MULTIPLIER;
    entity->fire_ticks_maximum = entity_type->fire_ticks_maximum;
}
void world_sync_tick_rate_for_living_entity(struct World *world, struct LivingEntity *living_entity, const struct EntityType *entity_type, const unsigned short no_damage_ticks_maximum) {
    struct Entity *entity = living_entity->damageable->entity;
    
    living_entity->no_damage_ticks *= TICKS_PER_SECOND_MULTIPLIER;
    living_entity->no_damage_ticks_maximum = no_damage_ticks_maximum;
    
    struct PotionEffect *potion_effects = living_entity->potion_effects;
    const unsigned short potion_effect_count = living_entity->potion_effect_count;
    for (int i = 0; i < potion_effect_count; i++) {
        potion_effects[i].duration *= TICKS_PER_SECOND_MULTIPLIER;
    }
    
    world_sync_tick_rate_for_entity(world, entity, entity_type);
}
void world_sync_tick_rate_for_player(struct World *world, struct PlayerConnection *player, const unsigned short no_damage_ticks_maximum) {
    world_sync_tick_rate_for_living_entity(world, player->player->living_entity, &ENTITY_TYPE_MINECRAFT_PLAYER, no_damage_ticks_maximum);
}
void world_change_tick_rate(struct World *world, const unsigned short tick_rate) {
    const unsigned int player_count = world->player_count;
    struct PlayerConnection *players = world->players;
    printf("updating tickrate values for %d player(s)...\n", player_count);
    const unsigned short maximumPlayerNoDamageTicksMaximum = ENTITY_TYPE_MINECRAFT_PLAYER.no_damage_ticks_maximum;
    for (int i = 0; i < player_count; i++) {
        struct PlayerConnection *connection = &players[i];
        world_sync_tick_rate_for_player(world, connection, maximumPlayerNoDamageTicksMaximum);
    }
    
    const int living_entity_count = world->living_entity_count;
    struct LivingEntity *living_entities = world->living_entities;
    for (int i = 0; i < living_entity_count; i++) {
        struct LivingEntity *living_entity = &living_entities[i];
        const struct EntityType *entity_type = living_entity->damageable->entity->type;
        world_sync_tick_rate_for_living_entity(world, living_entity, entity_type, entity_type->no_damage_ticks_maximum);
    }
}

void world_load_chunk(struct World *world, struct Chunk *chunk) {
    const int chunks_loaded = world->chunks_loaded_count;
    if (chunks_loaded + 1 <= world->chunks_loaded_count_maximum) {
        struct Chunk *chunks = world->chunks_loaded;
        memmove(&chunks[chunks_loaded], chunk, sizeof(struct Chunk));
        world->chunks_loaded_count += 1;
    }
}
void world_unload_chunk(struct World *world, struct Chunk *chunk) {
    const int chunks_loaded = world->chunks_loaded_count;
    struct Chunk *chunks = world->chunks_loaded;
    for (int i = 0; i < chunks_loaded; i++) {
        struct Chunk *targetChunk = &chunks[i];
        if (targetChunk == chunk) {
            const int chunk_memory_size = sizeof(struct Chunk);
            chunk_destroy(chunk);
            for (int j = i; j < chunks_loaded-1; j++) {
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
    struct PlayerConnection *players = world->players;
    for (int i = 0; i < player_count; i++) {
        if (players[i].player->living_entity->damageable->entity->uuid == player_uuid) {
            for (int j = i; j < player_count-1; j++) {
                world->players[j] = players[j+1];
            }
            break;
        }
    }
    world->player_count -= 1;
    server_player_quit(connection);
}
void world_player_joined(struct World *world, struct PlayerConnection *connection) {
    const unsigned int player_count = world->player_count;
    world->players[player_count] = *connection;
    world->player_count += 1;
}
