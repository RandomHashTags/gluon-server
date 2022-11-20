//
//  chunk.c
//  quark
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
    chunk->world = world;
    const size_t long_size = sizeof(long);
    memcpy((long *) &chunk->x, &x, long_size);
    memcpy((long *) &chunk->z, &z, long_size);
    return chunk;
}
void chunk_destroy(struct Chunk *chunk) {
    unsigned int living_entities_count;
    struct LivingEntity *living_entities;
    chunk_get_living_entities(chunk, &living_entities_count, &living_entities);
    for (unsigned int i = 0; i < living_entities_count; i++) {
        struct LivingEntity *living_entity = &living_entities[i];
        living_entity_destroy(living_entity);
    }
    
    free((struct World *) chunk->world);
    free(chunk);
}


void chunk_get_loaded_block_at_xyz(struct Chunk *chunk, const long x, const long y, const long z, struct Block *block) {
    block = NULL;
}

void chunk_get_living_entities(const struct Chunk *chunk, unsigned int *count, struct LivingEntity **entities) {
    const struct World *world = chunk->world;
    const unsigned int living_entities_count = world->living_entity_count;
    struct LivingEntity *living_entities = world->living_entities;
    
    unsigned int amount = 0;
    struct LivingEntity *filtered_living_entities[living_entities_count];
    for (unsigned int i = 0; i < living_entities_count; i++) {
        struct LivingEntity *living_entity = &living_entities[i];
        struct Chunk *living_entity_chunk = living_entity->damageable->entity->location->chunk;
        if (chunk == living_entity_chunk) {
            filtered_living_entities[amount] = living_entity;
            amount += 1;
        }
    }
    *count = amount;
    if (amount == 0) {
        entities = NULL;
        return;
    }
    for (unsigned int i = 0; i < amount; i++) {
        entities[i] = filtered_living_entities[i];
    }
}
