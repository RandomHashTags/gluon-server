//
//  world.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdlib.h>
#include <string.h>
#include "world.h"

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
}
void world_unload_chunk(struct World *world, struct Chunk *chunk) {
    const int chunks_loaded = world->chunks_loaded_count;
    struct Chunk *chunks = world->chunks_loaded;
    for (int i = 0; i < chunks_loaded; i++) {
        struct Chunk *targetChunk = &chunks[i];
        if (targetChunk == chunk) {
            const int chunkMemorySize = sizeof(struct Chunk);
            chunk_destroy(chunk);
            for (int j = i; j < chunks_loaded-1; j++) {
                memmove(&chunks[j], &chunks[j+1], chunkMemorySize);
            }
            world->chunks_loaded_count -= 1;
            break;
        }
    }
}
