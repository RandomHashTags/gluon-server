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

struct World *world_create(long seed) {
    struct World *world = malloc(sizeof(struct World));
    if (!world) {
        printf("failed to allocate memory for a World\n");
        return NULL;
    }
    memcpy((long *) world->seed, &seed, sizeof(seed));
    return world;
}
void world_destroy(struct World *world) {
    free((char *) world->name);
    
    const int chunks_loaded_count = world->chunks_loaded_count;
    struct Chunk *chunks = world->chunks_loaded;
    for (int i = 0; i < chunks_loaded_count; i++) {
        struct Chunk *chunk = &chunks[i];
        chunk_destroy(chunk);
    }
    free(chunks);
    
    free(world);
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
