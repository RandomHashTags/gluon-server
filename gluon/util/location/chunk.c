//
//  chunk.c
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chunk.h"

struct Chunk *chunk_create(struct World *world, const long x, const long z) {
    struct Chunk *chunk = malloc(sizeof(struct Chunk));
    if (!chunk) {
        printf("failed to allocate memory for a Chunk\n");
        return NULL;
    }
    struct Block **blocks = malloc(16 * 16 * 256 * sizeof(struct Block *)); // TODO: fix this
    if (!blocks) {
        free(chunk);
        printf("failed to allocate memory for a Chunk **blocks\n");
        return NULL;
    }
    
    chunk->world = world;
    const size_t long_size = sizeof(long);
    memcpy((long *) &chunk->x, &x, long_size);
    memcpy((long *) &chunk->z, &z, long_size);
    return chunk;
}
void chunk_destroy(struct Chunk *chunk) {
    unsigned int living_entities_count;
    struct LivingEntity **living_entities = chunk_get_living_entities(chunk, &living_entities_count);
    for (unsigned int i = 0; i < living_entities_count; i++) {
        struct LivingEntity *living_entity = living_entities[i];
        living_entity_destroy(living_entity);
    }
    
    const unsigned long data_count = chunk->data_count;
    struct ChunkData **data_loaded = chunk->data;
    for (unsigned long i = 0; i < data_count; i++) {
        struct ChunkData *data = data_loaded[i];
        chunk_data_destroy(data);
    }
    free(data_loaded);
    
    free((struct World *) chunk->world);
    free(chunk);
}

struct ChunkData *chunk_get_or_load_data(struct Chunk *chunk, const long y) {
    const unsigned long data_count = chunk->data_count;
    struct ChunkData **data = chunk->data;
    for (unsigned long i = 0; i < data_count; i++) {
        struct ChunkData *target_data = data[i];
        if (y >= target_data->min_y && y <= target_data->max_y) {
            return target_data;
        }
    }
    
    unsigned long blocks_count = 0;
    struct Block **blocks = NULL; // TODO: finish
    if (!blocks) {
        printf("chunk_get_or_load_data; failed to allocate memory for a ChunkData **blocks\n");
        return NULL;
    }
    const _Bool y_is_negative = y < 0;
    const long absolute_y = y_is_negative ? -y : y;
    long min_y = absolute_y - (absolute_y % 16), max_y = min_y + 16;
    if (y_is_negative) {
        min_y = -min_y;
        max_y = -max_y;
    }
    return chunk_data_create(min_y, max_y, blocks_count, blocks);
}
struct Block *chunk_get_loaded_block_at_xyz(struct Chunk *chunk, const long x, const long y, const long z) {
    const unsigned long data_count = chunk->data_count;
    struct ChunkData **data_loaded = chunk->data;
    for (unsigned long i = 0; i < data_count; i++) {
        struct ChunkData *data = data_loaded[i];
        if (y >= data->min_y && y <= data->max_y) {
            const unsigned long blocks_count = data->blocks_count;
            struct Block **blocks = data->blocks;
            for (unsigned long j = 0; j < blocks_count; j++) {
                struct Block *block = blocks[j];
                struct BlockLocation *block_location = block->location;
                if (block_location->x == x && block_location->y == y && block_location->z == z) {
                    return block;
                }
            }
            return NULL;
        }
    }
    return NULL;
}
struct LivingEntity **chunk_get_living_entities(const struct Chunk *chunk, unsigned int *count) {
    const struct World *world = chunk->world;
    const unsigned int living_entities_count = world->living_entity_count;
    struct LivingEntity **living_entities = world->living_entities;
    
    unsigned int amount = 0;
    struct LivingEntity *filtered_living_entities[living_entities_count];
    for (unsigned int i = 0; i < living_entities_count; i++) {
        struct LivingEntity *living_entity = living_entities[i];
        struct Chunk *living_entity_chunk = living_entity->damageable->entity->location->chunk;
        if (chunk == living_entity_chunk) {
            filtered_living_entities[amount] = living_entity;
            amount += 1;
        }
    }
    if (amount == 0) {
        return NULL;
    }
    *count = amount;
    struct LivingEntity **entities = alloca(amount * sizeof(struct LivingEntity *));
    for (unsigned int i = 0; i < amount; i++) {
        entities[i] = filtered_living_entities[i];
    }
    return entities;
}
