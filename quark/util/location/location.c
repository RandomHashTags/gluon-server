//
//  location.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "location.h"

struct Location *location_create(struct World *world, const long x, const long y, const long z, const unsigned x_float, const unsigned short y_float, const unsigned short z_float, const float yaw, const float pitch) {
    struct Location *location = malloc(sizeof(struct Location));
    if (!location) {
        printf("failed to allocate memory for a Location\n");
        return NULL;
    }
    location->world = world;
    location->x = x;
    location->y = y;
    location->z = z;
    location->x_float = x_float;
    location->y_float = y_float;
    location->z_float = z_float;
    location->yaw = yaw;
    location->pitch = pitch;
    return location;
}
void location_destroy(struct Location *location) {
    free((struct World *) location->world);
    free(location);
}

struct Chunk *location_get_chunk(struct Location *location) {
    const long chunkX = location->x / 16;
    const long chunkZ = location->z / 16;
    return NULL;
}
