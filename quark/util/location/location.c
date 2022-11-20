//
//  location.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "location.h"

struct Location *location_create(struct World *world, const float x, const float y, const float z, const float yaw, const float pitch) {
    struct Location *location = malloc(sizeof(struct Location));
    if (!location) {
        printf("failed to allocate memory for a Location\n");
        return NULL;
    }
    location->world = world;
    location->x = x;
    location->y = y;
    location->z = z;
    location->yaw = yaw;
    location->pitch = pitch;
    return location;
}
void location_destroy(struct Location *location) {
    free((struct World *) location->world);
    free(location);
}

struct Chunk *location_get_loaded_chunk(struct Location *location) {
    const struct World *world = location->world;
    const unsigned short chunk_size = 16;
    const long chunkX = location->x / chunk_size;
    const long chunkZ = location->z / chunk_size;
    const unsigned int chunks_loaded_count = world->chunks_loaded_count;
    struct Chunk *chunks_loaded = world->chunks_loaded;
    for (int i = 0; i < chunks_loaded_count; i++) {
        struct Chunk *chunk = &chunks_loaded[i];
        if (chunkX == chunk->x && chunkZ == chunk->z) {
            return chunk;
        }
    }
    return NULL;
}
